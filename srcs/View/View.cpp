#include <View/View.hpp>

extern float delta_time;

View::View(BlockMap *block_map)
{
    this->_window_app = new WindowApp();
    this->_player_info = new PlayerInfo();
    this->_map = new ViewMap(block_map);
    this->_skybox = new Skybox();

    this->_program_id = LoadShaders("./shaders/shader.vert", "./shaders/shader.frag");
    this->_skybox_id = LoadShaders("./shaders/skybox.vert", "./shaders/skybox.frag");
    this->_textu = loadpng("./textures/blocksv5.png");

    glUseProgram(this->_program_id);
    GLuint tex0Uni = glGetUniformLocation(this->_program_id, "tex");
	glUniform1i(tex0Uni, 0);

	this->_projection_id = glGetUniformLocation(this->_program_id, "Projection");
	this->_view_id = glGetUniformLocation(this->_program_id, "View");
	this->_model_id = glGetUniformLocation(this->_program_id, "Model");

    glUseProgram(this->_skybox_id);
	GLuint tex0Sky = glGetUniformLocation(this->_skybox_id, "skybox");
	glUniform1i(tex0Sky, 0);

	glClearColor(0.6f, 0.0f, 0.8f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glBindTexture(GL_TEXTURE_2D, this->_textu);
}

View::~View(void)
{
    delete this->_player_info;
    delete this->_window_app;
    delete this->_map;
    delete this->_skybox;
}

ViewMap *View::getViewMap(void)
{
    return this->_map;
}

WindowApp *View::getWindowApp(void)
{
    return this->_window_app;
}

PlayerInfo *View::getPlayerInfo(void)
{
    return this->_player_info;
}

Skybox *View::getSkybox(void)
{
    return this->_skybox;
}

GLuint &View::getProgramId(void)
{
    return this->_program_id;
}

GLuint &View::getTextu(void)
{
    return this->_textu;
}

GLuint &View::getProjectionId(void)
{
    return this->_projection_id;
}

GLuint &View::getViewId(void)
{
    return this->_view_id;
}

GLuint &View::getModelId(void)
{
    return this->_model_id;
}

GLuint &View::getSkyboxId(void)
{
    return this->_skybox_id;
}

void getDeltaTime(void) {
	static double last = glfwGetTime();

	double now = glfwGetTime();
	delta_time = (float)(now - last);
	last = now;
}

void View::updateUp(BlockMap *block_map, std::vector<ViewChunk *> *queueChunk)
{
    this->_map->updateUp(block_map, queueChunk);
}

void View::updateDown(BlockMap *block_map, std::vector<ViewChunk *> *queueChunk)
{
    this->_map->updateDown(block_map, queueChunk);
}

void View::updateLeft(BlockMap *block_map, std::vector<ViewChunk *> *queueChunk)
{
    this->_map->updateLeft(block_map, queueChunk);
}

void View::updateRight(BlockMap *block_map, std::vector<ViewChunk *> *queueChunk)
{
    this->_map->updateRight(block_map, queueChunk);
}