#include"Application.h"
#include"EntryPoint.h"
#include<iostream>

class ExampleApp : public Engine::Application {
public:
	ExampleApp() { std::cout << "siema"; }
	~ExampleApp() {}
};

Engine::Application* Engine::CreateApplication() { return new ExampleApp(); }