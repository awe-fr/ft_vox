#include <Controller/Controller.hpp>

float delta_time;

Controller::Controller(void)
{
    this->_model = new Model();
    this->_view = new View(this->_model->getBlockMap());
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
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
    while(app->IsClosed() == false) {
		/*temp*/
		getDeltaTime();
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
                ViewChunk *chunk = map->getChunk(j, i);
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

        glDepthFunc(GL_LEQUAL);
		glDisable(GL_CULL_FACE);
		glUseProgram(this->_view->getSkyboxId());
		view = glm::mat4(glm::mat3(glm::lookAt(-player->GivePosition(), (-player->GivePosition() + player->GiveDirection()), -player->GiveUp())));
		projection = glm::perspective(player->GiveFOV(), (float) WIDTH / (float)HEIGHT, 0.1f, 1010.0f);
		glUniformMatrix4fv(glGetUniformLocation(this->_view->getSkyboxId(), "view"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(this->_view->getSkyboxId(), "projection"), 1, GL_FALSE, &projection[0][0]);

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
            this->updateMap(current_pos, new_pos);
            current_pos = new_pos;
        }
		/*temp*/
	}
}

void Controller::updateMap(std::array<int, 2> prev_pos, std::array<int, 2> new_pos)
{
    if (new_pos[0] > prev_pos[0])
    {
        this->_model->updateRight();
        this->_view->updateRight(this->_model->getBlockMap());
    }
    else if (new_pos[0] < prev_pos[0])
    {
        this->_model->updateLeft();
        this->_view->updateLeft(this->_model->getBlockMap());
    }
    if (new_pos[1] > prev_pos[1])
    {
        this->_model->updateDown();
        this->_view->updateDown(this->_model->getBlockMap());
    }
    else if (new_pos[1] < prev_pos[1])
    {
        this->_model->updateUp();
        this->_view->updateUp(this->_model->getBlockMap());
    }
}
