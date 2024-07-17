#include "main.hpp"

int main()
{
	init();

	Camera cam;

	auto model = glm::mat4(1.f);

	glm::mat4 view = glm::lookAt(glm::vec3(0.0, -2.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0)); 
	//model = glm::translate(model, glm::vec3(-4, -3, 0.f));
	//model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	model = glm::rotate(model, -90.f, glm::vec3(1, 0, 0));

	auto mvp = cam.get_proj(800.f / 600) * cam.get_view() * model;
	glUseProgram(shader);
	glUniformMatrix4fv(MVP, 1, GL_FALSE, &mvp[0][0]);

	float (*mexican_hat)(float, float) = [](float x, float y) -> float
	{
		double t = hypotf(x, y) * 4.0;
		return (1 - t * t) * exp(-0.5 * t * t);
	};

	auto f1 = [](float x, float y) -> float
	{
		return x * pow(y, 3) - pow(x, 3) * y;
	};

	auto f2 = [](float x, float y) -> float
	{
		return pow(x, 2) + 3 * pow(y, 2) * exp(-pow(x, 2) * -pow(y, 2));
	};

	auto f3 = [](float x, float y) -> float
	{
		return -x * y * exp(-pow(x, 2) - pow(y, 2));
	};

	auto f4 = [](float x, float y) -> float
	{
		return -1.0 / (pow(x, 2) * pow(y, 2));
	};

	auto f5 = [](float x, float y) -> float
	{
		return cos(abs(x) + abs(y));
	};

	auto f6 = [](float x, float y) -> float
	{
		return cos(abs(x) + abs(y)) * (abs(x) + abs(y));
	};

	GLuint ind; 
	calculate(f6, vao, vbo, ebo, ind, { 1000, 1000 }, { 1,-1 }, { -1, 1 });

	double old_time = glfwGetTime();
	double new_time;
	float dt;

	while (!glfwWindowShouldClose(g_window))
	{
		new_time = glfwGetTime();
		dt = new_time - old_time;
		old_time = new_time;

		glfwPollEvents();


		if (glfwGetKey(g_window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(g_window, 1);


		if (glfwGetKey(g_window, GLFW_KEY_W))
			cam.move(cam.get_dir() * dt);
		if (glfwGetKey(g_window, GLFW_KEY_S))
			cam.move(-cam.get_dir() * dt);
		if (glfwGetKey(g_window, GLFW_KEY_A))
			cam.move(-cam.get_right() * dt);
		if (glfwGetKey(g_window, GLFW_KEY_D))
			cam.move(cam.get_right() * dt);
		if (glfwGetKey(g_window, GLFW_KEY_SPACE))
			cam.move(glm::vec3(0.f, 1.f, 0.f) * dt);
		if (glfwGetKey(g_window, GLFW_KEY_LEFT_SHIFT))
			cam.move(glm::vec3(0.f, -1.f, 0.f) * dt);
		
		if (glfwGetKey(g_window, GLFW_KEY_LEFT))
			cam.ProcessMouseMovement( -1000.f * dt, 0.f);
		if (glfwGetKey(g_window, GLFW_KEY_RIGHT))
			cam.ProcessMouseMovement(  1000.f * dt, 0.f);
		if (glfwGetKey(g_window, GLFW_KEY_UP))
			cam.ProcessMouseMovement(0.f, 1000.f * dt);
		if (glfwGetKey(g_window, GLFW_KEY_DOWN))
			cam.ProcessMouseMovement(0.f, -1000.f * dt);

		mvp = cam.get_proj(800.f / 600) * cam.get_view() * model;
		glUniformMatrix4fv(MVP, 1, GL_FALSE, &mvp[0][0]);

		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_LINES, ind, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(g_window);
	}

	return 0;
}