#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Core/Camera.hpp"
#include "Core/Entity.hpp"
#include "Core/Window.hpp"
#include "Core/Settings.hpp"
#include "Utils/Color.hpp"
#include "Utils/String.hpp"
#include "Debug/Debug.hpp"

namespace engine{
	Renderer::Renderer() : mEntityNumber(0), mLastFrameEntityNumber(0), mWindow(0), mCamera(0){
	}

	Renderer::~Renderer(){
	} 

	void Renderer::Init(Window &pWindow){
			mWindow = &pWindow;
			mWindowWidth = mWindow->GetWidth();
			mWindowHeight = mWindow->GetHeight();
    	
		// Initialisation de GLEW sous Windows
		#ifdef OOXWIN32
			glewExperimental = GL_TRUE;
			glewInit();

			if(!glewIsSupported("GL_VERSION_3_3"))
				throw Exception("GLEW : OpenGL Version 3.3 is not supported");
		#endif
				
		// Wireframe
		mSpecs.mWireframe = false;
		mSpecs.mWireframeChange = false;

		// Ambient Color 
		mSpecs.mAmbientColor = Settings::Call().GetSettingColor("AmbientColor");

		// FOV
		mSpecs.mFOV = Settings::Call().GetSettingFloat("FOV");

		// Near et Far plane
		mSpecs.mNearPlane = Settings::Call().GetSettingFloat("NearPlane");
		mSpecs.mFarPlane = Settings::Call().GetSettingFloat("FarPlane");

		m3DProjectionMatrix.PerspectiveFOV(mSpecs.mFOV, (f32)mWindowWidth / (f32)mWindowHeight, mSpecs.mNearPlane, mSpecs.mFarPlane);
		m2DProjectionMatrix.OrthoOffCenter(0,0,(f32)mWindowWidth,(f32)mWindowHeight);
	
	    // VSync
		mSpecs.mVsync = Settings::Call().GetSettingBool("VSync");
		mWindow->GetWindow().SetFramerateLimit(mSpecs.mVsync ? 60 : 0);

		// Activation du Z-Depth
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		// Activation du BackFace Culling
		mSpecs.mCullingFace= (Settings::Call().GetSettingStr("CullFace") == "CCW" ? GL_CCW : GL_CW);
		glFrontFace(mSpecs.mCullingFace);
		glEnable(GL_CULL_FACE);

		// Niveau d'anisotropy maximum
		f32 maxAniso;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
		mSpecs.mMaximumAnisotropy = (u32)maxAniso;

		// Niveau d'anisotropy demandé
		mSpecs.mWantedAnisotropy = Settings::Call().GetSettingInt("Anisotropy");
		if(mSpecs.mWantedAnisotropy > mSpecs.mMaximumAnisotropy){
			OmniLog << "Wanted Anisotropic Filtering Level is too high (" << mSpecs.mWantedAnisotropy << ")." << eol;
			mSpecs.mWantedAnisotropy = mSpecs.mMaximumAnisotropy;
		}

		// Entity Number drawn text
		mEntityNumberText.SetText(String("Entities : ")+mEntityNumber);
		mEntityNumberText.SetPosition(10,34);
		mEntityNumberText.SetColor(Color::White);
		mEntityNumberText.SetSize(12);		
	}

	void Renderer::SetFOV(f32 pFov){
		if(pFov >= 44.f){
			mSpecs.mFOV = pFov;
			m3DProjectionMatrix.PerspectiveFOV(mSpecs.mFOV, (f32)mWindowWidth / (f32)mWindowHeight, mSpecs.mNearPlane, mSpecs.mFarPlane);
			m3DViewProjMatrix = m3DViewMatrix * m3DProjectionMatrix;
		}
	}

	void Renderer::WireframeMode(bool pVal){
		mSpecs.mWireframe = pVal;
		mSpecs.mWireframeChange = true;
	}

	void Renderer::Resize(){
		mWindowWidth = mWindow->GetWidth();
		mWindowHeight = mWindow->GetHeight();
		m2DProjectionMatrix.OrthoOffCenter(0, 0, (f32)mWindowWidth, (f32)mWindowHeight);
		m3DProjectionMatrix.PerspectiveFOV(mSpecs.mFOV, (f32)mWindowWidth / (f32)mWindowHeight, mSpecs.mNearPlane, mSpecs.mFarPlane);
		m3DViewProjMatrix = m3DViewMatrix * m3DProjectionMatrix;
	}
	
	void Renderer::BeginScene(const Color &pColor) const{
		glClearColor(pColor.R(), pColor.G(), pColor.B(), pColor.A());
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void Renderer::EndScene(){
		mWindow->GetWindow().Display();
	}

	void Renderer::DrawText(Text* pText){
		mTextMap.push_back(pText);
	}

	void Renderer::DrawMesh(Mesh* pEntity){
		mMeshMap.push_back(pEntity);
	}
	
	void Renderer::DrawObject(Object* pEntity){
		mObjectMap.push_back(pEntity);
	}
	
	void Renderer::DrawDebugObject(DebugObject* pEntity){
		mDebugObjectMap.push_back(pEntity);
	}

	void Renderer::Render(){
		mEntityNumber = 0;

		if(mSpecs.mWireframeChange){
			mSpecs.mWireframeChange = false;
			if(mSpecs.mWireframe)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		if(!mMeshMap.empty())
			RenderMeshes();

		if(!mObjectMap.empty())
			RenderObjects();

		if(!mDebugObjectMap.empty())
			RenderDebugObjects();
		
		RenderTexts();
	}

	void Renderer::RenderTexts(){
		// Disable GL Depth and Culling for 2D text drawing
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

			for(mTextMapIt = mTextMap.begin(); mTextMapIt != mTextMap.end(); ++mTextMapIt){
				mWindow->GetWindow().Draw((*mTextMapIt)->GetSFMLText());
			}
			// Draw the entity number on screen if debug active
			#ifdef _DEBUG
				if(mEntityNumber != mLastFrameEntityNumber){
					mEntityNumberText.SetText(String("Entities : ")+mEntityNumber);
					mLastFrameEntityNumber = mEntityNumber;
				}
				mWindow->GetWindow().Draw(mEntityNumberText.GetSFMLText());
			#endif
			
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		mTextMap.clear();
	}

	void Renderer::RenderMeshes(){
		static Shader* currentShader;
		static Mesh* currentMesh;

		currentShader = 0;
		currentMesh = 0;
		
		// Using Textures
		glActiveTexture(GL_TEXTURE0);

		for(mMeshMapIt = mMeshMap.begin(); mMeshMapIt != mMeshMap.end(); ++mMeshMapIt){	
			// Get the current mesh
			currentMesh = (*mMeshMapIt);	
			
			// If the mesh possess a different shader, change it
			if(currentMesh->GetShader() != currentShader){
				currentShader = currentMesh->GetShader();
				currentShader->Bind();
			}

			// Send the Mesh Matrices to the Shader
			currentShader->SendMatrix4("ModelViewProjMatrix", currentMesh->GetModelMatrix() * m3DViewProjMatrix );
			currentShader->SendMatrix4("ModelViewMatrix", currentMesh->GetModelMatrix() * m3DViewMatrix);
			currentShader->SendMatrix4("ViewMatrix", m3DViewMatrix);
			currentShader->SendMatrix4("NormalMatrix", m3DNormalMatrix);

			// Send the Mesh Material to the Shader
			currentShader->SendColor("Ka", currentMesh->GetMaterial().mAmbient);
			currentShader->SendColor("Kd", currentMesh->GetMaterial().mDiffuse);
			currentShader->SendColor("Ks", currentMesh->GetMaterial().mSpecular);
			currentShader->SendFloat("shininess", currentMesh->GetMaterial().mShininess);

			// Bind texture
			currentMesh->GetTexture().Bind();

			// Draw the mesh
			currentMesh->GetMesh()->Bind();
				glDrawElements(GL_TRIANGLES, currentMesh->GetMesh()->GetIndexCount(), GL_UNSIGNED_INT, 0);
			currentMesh->GetMesh()->UnBind();

			// Unbind texture
			currentMesh->GetTexture().UnBind();
		}
		currentShader->UnBind();
		
		// Add Mesh number to total
		mEntityNumber += mMeshMap.size();
		
		// Clear the vector for next frame
		mMeshMap.clear();
	}

	void Renderer::RenderObjects(){
		static Shader* currentShader;
		static Object* currentObject;

		currentShader = 0;
		currentObject = 0;

		for(mObjectMapIt = mObjectMap.begin(); mObjectMapIt != mObjectMap.end(); ++mObjectMapIt){	
			// Get the current Object
			currentObject = (*mObjectMapIt);			
			
			// If the object possess a different shader, change it
			if(currentObject->GetShader() != currentShader){
				currentShader = currentObject->GetShader();
				currentShader->Bind();
			}

			// Send the Object Matrices to the Shader
			currentShader->SendMatrix4("ModelViewProjMatrix", currentObject->GetModelMatrix() * m3DViewProjMatrix );
			currentShader->SendMatrix4("ModelViewMatrix", currentObject->GetModelMatrix() * m3DViewMatrix);
			currentShader->SendMatrix4("ViewMatrix", m3DViewMatrix);
			currentShader->SendMatrix4("NormalMatrix", m3DNormalMatrix);

			// Send the Object Material to the Shader
			currentShader->SendColor("Ka", currentObject->GetMaterial().mAmbient);
			currentShader->SendColor("Kd", currentObject->GetMaterial().mDiffuse);
			currentShader->SendColor("Ks", currentObject->GetMaterial().mSpecular);
			currentShader->SendFloat("shininess", currentObject->GetMaterial().mShininess);

			// Draw the Object
			currentObject->GetMesh()->Bind();
				glDrawElements(GL_TRIANGLES, currentObject->GetMesh()->GetIndexCount(), GL_UNSIGNED_INT, 0);
			currentObject->GetMesh()->UnBind();

		}
		currentShader->UnBind();
		
		// Add Object number to total
		mEntityNumber += mObjectMap.size();

		// Clear the vector for next frame
		mObjectMap.clear();
	}

	void Renderer::RenderDebugObjects(){
		static Shader* currentShader;
		static DebugObject* currentObject;

		currentShader = 0;
		currentObject = 0;
		
		// Using Texture
		glActiveTexture(GL_TEXTURE0);

		for(mDebugObjectMapIt = mDebugObjectMap.begin(); mDebugObjectMapIt != mDebugObjectMap.end(); ++mDebugObjectMapIt){			
			// Get the current Object
			currentObject = (*mDebugObjectMapIt);			

			// If the object possess a different shader, change it
			if(currentObject->GetShader() != currentShader){
				currentShader = currentObject->GetShader();
				currentShader->Bind();
			}
			
			// Send the Object matrices to the shader
			currentShader->SendMatrix4("ModelViewProjMatrix", currentObject->GetModelMatrix() * m3DViewProjMatrix );
			currentShader->SendMatrix4("ModelViewMatrix", currentObject->GetModelMatrix() * m3DViewMatrix);
			currentShader->SendMatrix4("ViewMatrix", m3DViewMatrix);
			currentShader->SendMatrix4("NormalMatrix", m3DNormalMatrix);

			// Send the Object material to the shader
			currentShader->SendColor("Ka", currentObject->GetMaterial().mAmbient);
			currentShader->SendColor("Kd", currentObject->GetMaterial().mDiffuse);
			currentShader->SendColor("Ks", currentObject->GetMaterial().mSpecular);
			currentShader->SendFloat("shininess", currentObject->GetMaterial().mShininess);

			// Bind Texture
			currentObject->GetTexture().Bind();

			// Draw the Object
			currentObject->GetMesh()->Bind();
				glDrawElements(GL_TRIANGLES, currentObject->GetMesh()->GetIndexCount(), GL_UNSIGNED_INT, 0);
			currentObject->GetMesh()->UnBind();

			// Unbind texture
			currentObject->GetTexture().UnBind();
		}
		currentShader->UnBind();
		
		// Add DebugObject number to total
		mEntityNumber += mDebugObjectMap.size();

		// Clear the vector for next frame
		mDebugObjectMap.clear();
	}
}
