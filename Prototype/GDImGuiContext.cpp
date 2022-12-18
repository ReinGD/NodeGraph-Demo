/*====================
	MADE BY REINGD
====================*/
#include "GDImGuiContext.h"
#include "NodeGraph.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


void GDImGuiContext::Create(GLFWwindow* window, int windowWitdh, int windowHeight)
{
	//GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

	auto context = privGetInstance();
	context->windowWitdh = windowWitdh;
	context->windowHeight = windowHeight;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.WantCaptureKeyboard = true;
	io.WantCaptureMouse = true;

	io.ConfigWindowsMoveFromTitleBarOnly = true;

	ImGui::StyleColorsDark();
	io.Fonts->AddFontFromFileTTF("extra_font/DroidSans.ttf", 24);
	io.FontGlobalScale = 1.0;
	context->window = window;

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(context->window, true); //callbacks are already implemented, installcallbacks would keep track of the originals
	ImGui_ImplOpenGL3_Init(glsl_version);


	NodeGraph::DEFAULT_SCREEN_SIZE = ImVec2(context->windowWitdh, context->windowHeight);
}

void GDImGuiContext::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

}

void GDImGuiContext::Update()
{
	auto context = privGetInstance();


	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;


	NodeGraph::Update();

	//send to buffer
	ImGui::Render();
}

void GDImGuiContext::Draw()
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

GDImGuiContext::GDImGuiContext()
{
}

GDImGuiContext::~GDImGuiContext()
{
}

GDImGuiContext* GDImGuiContext::privGetInstance()
{
	static GDImGuiContext instance;
	return &instance;
}
