#include "Scene.hpp"
#include "Debug/New.hpp"

using namespace engine;
/*
GameScene::GameScene(const std::string &pName) : Scene(pName){
}

GameInput::GameInput(const std::string &pName) : Input(pName){

}

bool GameScene::Start(){
		
	// Recuperation de la fenetre
	mWindow = &(mKernel->GetWindow().GetWindow());
	
	currRenderer = CRenderer::Get();
	
	cam.SetProjectionMatrix(currRenderer->Get3DProjectionMatrix());
	cam.LookAt(Vector3F(0.5f,0,1), Vector3F(-2.5f,2,4));

	currRenderer->SetCamera(&cam);

	TextureShader.Compile("shaderTexture.vs", "shaderTexture.fs");

	ColorShader.Compile("shaderColor.vs", "shaderColor.fs");


	Image img;
	img.LoadFromFile("crate.jpg");
	tex1.LoadFromImage(img);

	obj1.MakeCube("carre", ColorShader);
	obj1.GetMaterial().mAmbient = Color(0.f, 0.08f, 0.08f);
	obj1.GetMaterial().mDiffuse = Color(0.f, 0.8f, 0.8f);
	obj2.GetMaterial().mSpecular = Color(0.0f, 0.5f, 0.5f);
	obj1.GetMaterial().mShininess = 50.f;
	obj1.Translate(Vector3F(-0.5f,0,0));

	//obj2.CopyObject(obj1);
	obj2.MakeSphere("sphere", ColorShader, 6);
	obj2.GetMaterial().mAmbient = Color(0.8f, 0.32f, 0.f);
	obj2.GetMaterial().mDiffuse = Color(2.f, 0.8f, 0.f);
	obj2.GetMaterial().mSpecular = Color(0.8f, 0.32f, 0.f);
	obj2.GetMaterial().mShininess = 50.f;

	//obj2.Scale(12,0.2f,12);
	//obj2.Translate(Vector3F(2,-1.1f,0));
	obj2.Translate(Vector3F(2,0,0));

	mesh1.MakeCube("carretex", TextureShader);
	mesh1.SetTexture(tex1);
	mesh1.SetPosition(Vector3F(5,0,1.5));
	obj2.GetMaterial().mAmbient = Color(0,0,0);

//	fps.SetFont("DejaVuSans.ttf", 12);
//	fps.SetPosition(Vector2F(10,25));
//	fps.SetColor(Color::White);
//	fps.SetText("dur");

//	mousePos.SetFont("DejaVuSans.ttf", 12);
//	mousePos.SetPosition(Vector2F(10,10));
//	mousePos.SetColor(Color::White);
//	mousePos.SetText("hur");

	l.SetPosition(Vector3F(1,3,1.5));
	l.SetDiffuse(Color(1.f,1.f,1.f));
	l.SetRange(8);
	
	ColorShader.Bind();
	ColorShader.SendColor("ambientColor", currRenderer->GetSpecifications().mAmbientColor);
	ColorShader.SendFloat("constantAtt", l.GetAttenuationConstant());
	ColorShader.SendFloat("linearAtt", l.GetAttenuationLinear());
	ColorShader.SendFloat("quadraticAtt", l.GetAttenuationQuadratic());
	ColorShader.SendFloat("range", l.GetRange());
	
	ColorShader.SendVector3("lightPosition", l.GetPosition());
	ColorShader.SendColor("lightColor", l.GetDiffuse());
	ColorShader.UnBind();
	
	TextureShader.Bind();
	TextureShader.SendColor("ambientLight", currRenderer->GetSpecifications().mAmbientColor);
	ColorShader.SendFloat("constantAtt", l.GetAttenuationConstant());
	ColorShader.SendFloat("linearAtt", l.GetAttenuationLinear());
	ColorShader.SendFloat("quadraticAtt", l.GetAttenuationQuadratic());
	ColorShader.SendFloat("range", l.GetRange());

	TextureShader.SendVector3("lightPosition", l.GetPosition());
	TextureShader.SendColor("lightColor", l.GetDiffuse());
	TextureShader.UnBind();

	return true;
}

void GameScene::Stop(){

}

void GameInput::SingleEvents(){
	while(mKernel->GetWindow().GetWindow().GetEvent(mInput.GetEvent())){
		// fermeture si escape ou croix
		if(mInput.GetEventType() == sf::Event::Closed || mInput.IsKeyDown(sf::Key::Escape))
			mKernel->KillAllTasks();
		
		if(mInput.IsKeyHit(sf::Key::B))
			mScene->obj1.Rotate(Vector3F::UNIT_X, Math::Pi/4.f);

		if(mInput.IsMouseHit(sf::Mouse::Right)){
			// sauvegarde de l'endroit du clic
			xClick = mInput.GetMouseX();
			yClick = mInput.GetMouseY();
			// on cache le curseur
			mKernel->GetWindow().ShowCursor(false);
			// deplacement de la souris au milieu de la fenetre
			mKernel->GetWindow().SetCursorPosition(mKernel->GetWindow().GetHalfWidth(), mKernel->GetWindow().GetHalfHeight());
		}

		if(mInput.IsMouseUp(sf::Mouse::Right)){
			// On replace la souris a l'emplacement du click
			mKernel->GetWindow().SetCursorPosition(xClick,yClick);
			// on remontre le curseur
			mKernel->GetWindow().ShowCursor(true);
		}

		if(mInput.IsKeyHit(sf::Key::W))
			mScene->currRenderer->SetWireframe(!mScene->currRenderer->GetWireframe());
	}
}

void GameInput::RepetedEvents(){

	// Mouvement de la camera
	if(mInput.IsKeyDown(sf::Key::Z)) {mScene->cam.MoveForward(1.f * mScene->elapsedTime); }
	if(mInput.IsKeyDown(sf::Key::S)) {mScene->cam.MoveForward(-1.f * mScene->elapsedTime); }
	if(mInput.IsKeyDown(sf::Key::D)) {mScene->cam.MoveRight(1.f * mScene->elapsedTime); }
	if(mInput.IsKeyDown(sf::Key::Q)) {mScene->cam.MoveRight(-1.f * mScene->elapsedTime); }
	if(mInput.IsKeyDown(sf::Key::A)) {mScene->cam.MoveUp(1.f * mScene->elapsedTime); }
	if(mInput.IsKeyDown(sf::Key::E)) {mScene->cam.MoveUp(-1.f * mScene->elapsedTime); }

			
		if(mInput.IsKeyDown(sf::Key::Up))
			mScene->obj1.Translate(Vector3F(0,0,-0.1f));
		if(mInput.IsKeyDown(sf::Key::Down))
			mScene->obj1.Translate(Vector3F(0,0,0.1f));
		if(mInput.IsKeyDown(sf::Key::Left))
			mScene->obj1.Translate(Vector3F(-0.1f,0,0));
		if(mInput.IsKeyDown(sf::Key::Right))
			mScene->obj1.Translate(Vector3F(0.1f,0,0));

	// Vitesse de la camera
	if(mInput.IsKeyDown(sf::Key::LShift))	mScene->cam.SetSpeed(20);
	else									mScene->cam.SetSpeed(5);
	
	// Orientation de la camera
	if(mKernel->GetInput().IsMouseDown(sf::Mouse::Right)){
		// on recupere les coordonnees du deplacement
		x = mInput.GetMouseX();
		y = mInput.GetMouseY();
		
		// on bouge la camera en fonction de ce mouvement
		mScene->cam.Yaw((x - mKernel->GetWindow().GetHalfWidth()) * mScene->elapsedTime);
		mScene->cam.Pitch((y - mKernel->GetWindow().GetHalfHeight()) * mScene->elapsedTime);

		// On replace le curseur au point 
		mKernel->GetWindow().SetCursorPosition(mKernel->GetWindow().GetHalfWidth(),mKernel->GetWindow().GetHalfHeight());
	}
	
}

void GameScene::Update(){
	// Mise a jour de la clock
	elapsedTime = clk.GetElapsedTime();
	clk.Reset();
		
	
	// Affichage des fps
	if(fpsTimer.GetElapsedTime() > 1){
	//	fps.SetText(String(1.f/elapsedTime));	
		fpsTimer.Reset();
	}
			
	// Affichage des coordonnees souris
	//mousePos.SetText(String("X: ") + mKernel->GetInput().GetMouseX() + " Y: " + mKernel->GetInput().GetMouseY());
		
	// Envoi des entites a dessiner au Renderer
	//mousePos.Draw();
	//fps.Draw(); 

	if(cam.GetFrustum().CubeInFrustum(mesh1.GetAABB()))
		mesh1.Draw();

	if(cam.GetFrustum().CubeInFrustum(obj1.GetAABB()))
		obj1.Draw();

	if(cam.GetFrustum().CubeInFrustum(obj2.GetAABB()))
		obj2.Draw();

	// Rendu
	currRenderer->BeginScene(Color(0.f,0.f,0.f,1.f));
		currRenderer->Render();
	currRenderer->EndScene();
}
*/