#include <Controller/Controller.hpp>

float delta_time;

Controller::Controller(void)
{
    this->_model = new Model();
    this->_view = new View(this->_model->getBlockMap());
    this->_closeThread = false;
    for (int i = 0; i <= RENDER_DISTANCE * 2; i++) {
        for (int j = 0; j <= RENDER_DISTANCE * 2; j++) {
            this->_binder[i][j] = 1;
        }
    }
}

Controller::~Controller(void)
{
    delete this->_view;
    delete this->_model;
}

void Controller::loop(void)
{
    WindowApp *app = this->_view->getWindowApp();
    PlayerInfo *player = this->_view->getPlayerInfo();
    Skybox *skybox = this->_view->getSkybox();
    std::array<int, 2> current_pos = player->getChunkPos();
    std::thread render(Controller::routineThread, this, &current_pos, player, app);
    while(app->IsClosed() == false) {
		/*temp*/
		getDeltaTime();
        if (1 / delta_time <= 200)
		    std::cout << 1 / delta_time << std::endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_CULL_FACE);

		glUseProgram(this->_view->getProgramId());
        

		glm::mat4 model = glm::mat4(1.0f);

        ViewMap *map = this->_view->getViewMap();
        player = this->_view->getPlayerInfo();

        model = glm::translate(model, glm::vec3(-RENDER_DISTANCE * CHUNK_SIZE + current_pos[0] * CHUNK_SIZE, 0, -RENDER_DISTANCE * CHUNK_SIZE + current_pos[1] * CHUNK_SIZE));
        glBindTexture(GL_TEXTURE_2D, this->_view->getTextu());
        for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        {
            for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            {
                // std::chrono::time_point<std::chrono::system_clock> start, end;
                // start = std::chrono::system_clock::now();
                ViewChunk *chunk = map->getChunk(j, i);
                if (this->_binder[i][j] == 1) {
                    isOkayToBind(i, j, chunk, false);
                    // for (size_t t = j; t <= RENDER_DISTANCE * 2; t++)
                    model = glm::translate(model, glm::vec3(CHUNK_SIZE, 0, 0));
                    
                    continue;
                    // chunk->bindBuffer();
                    // this->_binder[i][j] = 0;
                }
                // end = std::chrono::system_clock::now();
                // std::chrono::duration<double> elapsed_seconds = end - start;
                // if (elapsed_seconds.count() >= 0.0005)
                //     std::cout << elapsed_seconds.count() << std::endl;
                glBindVertexArray(chunk->GiveVAO());
                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, chunk->GiveGlTextureBuffer());
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

                glUniformMatrix4fv(this->_view->getProjectionId(), 1, GL_FALSE, &player->GiveProjection()[0][0]);
                glUniformMatrix4fv(this->_view->getViewId(), 1, GL_FALSE, &player->GiveView()[0][0]);
                glUniformMatrix4fv(this->_view->getModelId(), 1, GL_FALSE, &model[0][0]);

                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, chunk->GiveGlVertexBuffer());
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

                glDrawArrays(GL_TRIANGLES, 0, chunk->GiveVertexBufferSize());
                glDisableVertexAttribArray(0);
                model = glm::translate(model, glm::vec3(CHUNK_SIZE, 0, 0));
            }
            model = glm::translate(model, glm::vec3(-(RENDER_DISTANCE * 2 + 1) * CHUNK_SIZE, 0, CHUNK_SIZE));
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
        // std::array<int, 2> new_pos = player->getChunkPos();
        // if (new_pos != current_pos)
        // {
        //     this->updateMap(current_pos, new_pos);
        //     current_pos = new_pos;
        // }
		/*temp*/
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
        this->_binder[i][j] = 0;
        bind = true;
    }
}

void Controller::routineThread(Controller *control, std::array<int, 2> *current_pos, PlayerInfo *player, WindowApp *app) {
    while(control->_closeThread == false) {
        std::array<int, 2> new_pos = player->getChunkPos();
        if (new_pos != *current_pos)
        {
            control->updateMap(control, *current_pos, new_pos);
            *current_pos = new_pos;
        }
    }
}

void Controller::updateMap(Controller *control, std::array<int, 2> prev_pos, std::array<int, 2> new_pos)
{
    if (new_pos[0] > prev_pos[0])
    {
        this->_model->updateRight();
        this->_view->updateRight(this->_model->getBlockMap());
        for (int i = 0; i <= RENDER_DISTANCE * 2; i++) {
            control->_binder[i][RENDER_DISTANCE * 2] = 1;
        }
    }
    else if (new_pos[0] < prev_pos[0])
    {
        this->_model->updateLeft();
        this->_view->updateLeft(this->_model->getBlockMap());
        for (int i = 0; i <= RENDER_DISTANCE * 2; i++) {
            control->_binder[i][0] = 1;
        }
    }
    if (new_pos[1] > prev_pos[1])
    {
        this->_model->updateDown();
        this->_view->updateDown(this->_model->getBlockMap());
        for (int i = 0; i <= RENDER_DISTANCE * 2; i++) {
            control->_binder[RENDER_DISTANCE * 2][i] = 1;
        }
    }
    else if (new_pos[1] < prev_pos[1])
    {
        this->_model->updateUp();
        this->_view->updateUp(this->_model->getBlockMap());
        for (int i = 0; i <= RENDER_DISTANCE * 2; i++) {
            control->_binder[0][i] = 1;
        }
    }
}
