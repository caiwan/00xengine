#include "Scene.hpp"
#include "Debug/New.hpp"
#include <iostream>

using namespace engine;


f32 ElapsedTime;
bool paused = false;

int main(){
	try{
		ILogger::Init();
		Settings::Call().Parse();
		ResourceManager::Call().AddPath("Data/shaders", "Shader");
		ResourceManager::Call().AddPath("Data/textures", "Image");

		{
			Window myWindow;
			Image Crate;
			Texture CrateTexture;
			Text FPSText, MousePosText;
			Clock FrameClock, FpsClock;
		
			Input myInput;
			myInput.Init(myWindow);

			Renderer& myRenderer = Renderer::Call();
			myRenderer.Init(myWindow);
		
			Crate.LoadFromFile("crate.jpg");
			CrateTexture.LoadFromImage(Crate);

			Light l;
			l.SetPosition(Vector3F(1,3,1.5));
			l.SetDiffuse(Color(1.f,1.f,1.f));
			l.SetRange(8);

			Shader ColorShader;
			ColorShader.Compile("shaderColor.vs", "shaderColor.fs");
			ColorShader.Bind();
			ColorShader.SendColor("ambientColor", myRenderer.GetSpecifications().mAmbientColor);
			ColorShader.SendFloat("constantAtt", l.GetAttenuationConstant());
			ColorShader.SendFloat("linearAtt", l.GetAttenuationLinear());
			ColorShader.SendFloat("quadraticAtt", l.GetAttenuationQuadratic());
			ColorShader.SendFloat("range", l.GetRange());
	
			ColorShader.SendVector3("lightPosition", l.GetPosition());
			ColorShader.SendColor("lightColor", l.GetDiffuse());
			ColorShader.UnBind();

			Object obj1;
			obj1.MakeCube("cube", ColorShader);
			obj1.GetMaterial().mAmbient = Color(0.f, 0.08f, 0.08f);
			obj1.GetMaterial().mDiffuse = Color(0.f, 0.8f, 0.8f);
			obj1.GetMaterial().mSpecular = Color(0.0f, 0.5f, 0.5f);
			obj1.GetMaterial().mShininess = 50.f;

			Camera cam;
			cam.LookAt(Vector3F(0.5f,0,1), Vector3F(-2.5f,2,4));
		
			FPSText.SetSize(12);
			FPSText.SetPosition(10,10);
			MousePosText.SetSize(12);
			MousePosText.SetPosition(10,22);

			while(myWindow.IsOpened()){
				ElapsedTime = FrameClock.GetElapsedTime();
				FrameClock.Reset();

				if(FpsClock.GetElapsedTime() > 1.f){
					FPSText.SetText(String(1.f/ElapsedTime));
					FpsClock.Reset();
				}

			
				while(myInput.GetEvent()){
					if(myInput.GetEventType() == sf::Event::Closed)
						myWindow.Close();

					if(myInput.IsKeyHit(Space))
						if(!paused){
							paused = true;
							FrameClock.Pause();
						}else{
							paused = false;
							FrameClock.Resume();
						}
				}

				MousePosText.SetText(String("X : ")+myInput.GetMouseX()+" Y : "+myInput.GetMouseY());
			
				MousePosText.Draw();
				FPSText.Draw();
				obj1.Draw();

				myRenderer.BeginScene(myRenderer.GetSpecifications().mAmbientColor);
					myRenderer.Render();
				myRenderer.EndScene();
			}
		}
	}catch(Exception e){
		std::cout << e.what() << std::endl;
		system("PAUSE");
	}

	Renderer::Kill();
	ResourceManager::Kill();
	Settings::Kill();
	ILogger::Kill();
	#ifdef _DEBUG
		MemoryManager::Kill();
	#endif

    return 0;
}