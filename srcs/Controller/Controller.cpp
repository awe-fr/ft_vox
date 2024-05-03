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
    while(app->IsClosed() == false) {
		/*temp*/
		getDeltaTime();
		std::cout << 1 / delta_time << std::endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(this->_view->getProgramId());

		glm::mat4 Model = glm::mat4(1.0f);

        ViewMap *map = this->_view->getViewMap();
        PlayerInfo *player = this->_view->getPlayerInfo();

        Model = glm::translate(Model, glm::vec3(-RENDER_DISTANCE * CHUNK_SIZE, 0, - RENDER_DISTANCE * CHUNK_SIZE));
        for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        {
            for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            {
                ViewChunk *chunk = map->getChunk(j, i);
                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, chunk->GiveGlTextureBuffer());
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

                glUniformMatrix4fv(this->_view->getProjectionId(), 1, GL_FALSE, &player->GiveProjection()[0][0]);
                glUniformMatrix4fv(this->_view->getViewId(), 1, GL_FALSE, &player->GiveView()[0][0]);
                glUniformMatrix4fv(this->_view->getModelId(), 1, GL_FALSE, &Model[0][0]);

                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, chunk->GiveGlVertexBuffer());
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
                glDrawArrays(GL_TRIANGLES, 0, chunk->GiveVertexBufferSize());
                glDisableVertexAttribArray(0);
                Model = glm::translate(Model, glm::vec3(CHUNK_SIZE, 0, 0));
            }
            Model = glm::translate(Model, glm::vec3(-(RENDER_DISTANCE * 2 + 1) * CHUNK_SIZE, 0, CHUNK_SIZE));
        }

		player->Movements(app->GiveWindow());
		/*temp*/
	}
}