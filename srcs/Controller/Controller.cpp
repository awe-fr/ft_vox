#include <Controller/Controller.hpp>

float delta_time;

Controller::Controller(void)
{
    this->_model = new Model();
    this->_view = new View(this->_model->getBlockMap());
    this->_closeThread = false;
}

Controller::~Controller(void)
{
    delete this->_view;
    delete this->_model;
}

std::mutex stop;

void Controller::loop(void)
{
    WindowApp *app = this->_view->getWindowApp();
    PlayerInfo *player = this->_view->getPlayerInfo();
    Skybox *skybox = this->_view->getSkybox();
    std::array<int, 2> current_pos = player->getChunkPos();
    
    std::thread render(Controller::routineThread, this, &current_pos, player, app);
    while(app->IsClosed() == false) {
		getDeltaTime();
        // if (1 / delta_time <= 200)
		//     std::cout << 1 / delta_time << std::endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glUseProgram(this->_view->getProgramId());

        ViewMap *map = this->_view->getViewMap();
        player = this->_view->getPlayerInfo();

        GLuint trans = glGetUniformLocation(this->_view->getProgramId(), "trans");

        glBindTexture(GL_TEXTURE_2D, this->_view->getTextu());
        for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        {
            for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            {
                ViewChunk *chunk = map->getChunk(j, i);
                if (chunk->IsBinded() == false) {
                    isOkayToBind(i, j, chunk, false);
                    continue;
                }
                glBindVertexArray(chunk->GiveVAO());
                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, chunk->GiveGlTextureBuffer());
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

                glUniformMatrix4fv(this->_view->getProjectionId(), 1, GL_FALSE, &player->GiveProjection()[0][0]);
                glUniformMatrix4fv(this->_view->getViewId(), 1, GL_FALSE, &player->GiveView()[0][0]);
                glUniformMatrix4fv(this->_view->getModelId(), 1, GL_FALSE, &chunk->GiveModel()[0][0]);

                glUniform1f(trans, 1);

                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, chunk->GiveGlVertexBuffer());
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

                glDrawArrays(GL_TRIANGLES, 0, chunk->GiveVertexBufferSize());                
            }
        }
        for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        {
            for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            {
                ViewChunk *chunk = map->getChunk(j, i);
                if (chunk->IsBinded() == false) {
                    continue;
                }
                if (chunk->GiveVertexBufferSizeWaheur() != 0) {
                    glBindVertexArray(chunk->GiveVAOWaheur());
                    glEnableVertexAttribArray(1);
                    glBindBuffer(GL_ARRAY_BUFFER, chunk->GiveGlTextureBufferWaheur());
                    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

                    glUniformMatrix4fv(this->_view->getProjectionId(), 1, GL_FALSE, &player->GiveProjection()[0][0]);
                    glUniformMatrix4fv(this->_view->getViewId(), 1, GL_FALSE, &player->GiveView()[0][0]);
                    glUniformMatrix4fv(this->_view->getModelId(), 1, GL_FALSE, &chunk->GiveModel()[0][0]);

                    glUniform1f(trans, 0.7);

                    glEnableVertexAttribArray(0);
                    glBindBuffer(GL_ARRAY_BUFFER, chunk->GiveGlVertexBufferWaheur());
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

                    glDrawArrays(GL_TRIANGLES, 0, chunk->GiveVertexBufferSizeWaheur());
                }
                glDisableVertexAttribArray(0);
            }
        }
        isOkayToBind(0, 0, NULL, true);

        glDepthFunc(GL_LEQUAL);
		glDisable(GL_CULL_FACE);
		glUseProgram(this->_view->getSkyboxId());
		skybox->SetView(glm::mat4(glm::mat3(glm::lookAt(player->GivePosition(), player->GivePosition() + player->GiveDirection(), player->GiveUp()))));
		skybox->SetProjection(glm::perspective(glm::radians(player->GiveFOV()), (float) WIDTH / (float)HEIGHT, 0.1f, 1010.0f));
		glUniformMatrix4fv(glGetUniformLocation(this->_view->getSkyboxId(), "view"), 1, GL_FALSE, &skybox->GiveView()[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(this->_view->getSkyboxId(), "projection"), 1, GL_FALSE, &skybox->GiveProjection()[0][0]);

		glBindVertexArray(skybox->GiveVAO());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->GiveCubemapTexture());
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glDepthFunc(GL_LESS);

		player->Movements(app->GiveWindow());
        std::array<int, 2> new_pos = player->getChunkPos();
        if (new_pos != current_pos)
        {
            stop.lock();
            this->queue.push_back(CustomVec{current_pos, new_pos});
            stop.unlock();
            current_pos = new_pos;
        }
        stop.lock();
        if (!this->queueChunk.empty()) {
            ViewChunk *temp = this->queueChunk.front();
            this->queueChunk.erase(this->queueChunk.begin());
            delete temp;
        }
        stop.unlock();
	}
    this->_closeThread = true;
    render.join();
}

void Controller::isOkayToBind(int i, int j, ViewChunk *chunk, bool reset) {
    static bool bind = false;
    if (reset == true) {
        bind = false;
    }
    else if (reset == false && bind == false){
        chunk->bindBuffer();
        bind = true;
    }
}

void Controller::routineThread(Controller *control, std::array<int, 2> *current_pos, PlayerInfo *player, WindowApp *app) {
    while(control->_closeThread == false) {
        stop.lock();
        if (control->queue.empty() == false) {
            CustomVec temp = control->queue.front();
            control->queue.erase(control->queue.begin());
            stop.unlock();
            control->updateMap(control, temp._older, temp._new);
        }
        else
            stop.unlock();
    }
}

void Controller::updateMap(Controller *control, std::array<int, 2> prev_pos, std::array<int, 2> new_pos)
{
    if (new_pos[0] > prev_pos[0])
    {
        control->_model->updateRight();
        control->_view->updateRight(control->_model->getBlockMap(), &control->queueChunk);
    }
    else if (new_pos[0] < prev_pos[0])
    {
        control->_model->updateLeft();
        control->_view->updateLeft(control->_model->getBlockMap(), &control->queueChunk);
    }
    if (new_pos[1] > prev_pos[1])
    {
        control->_model->updateDown();
        control->_view->updateDown(control->_model->getBlockMap(), &control->queueChunk);
    }
    else if (new_pos[1] < prev_pos[1])
    {
        control->_model->updateUp();
        control->_view->updateUp(control->_model->getBlockMap(), &control->queueChunk);
    }
}
