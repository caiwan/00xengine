#ifndef RENDERER_HPP
#define RENDER_HPP

#include <map>
#include "Text.hpp"
#include "Texture.hpp"
#include "Math/Matrix4.hpp"
#include "Utils/Singleton.hpp"
#include "Core/Enums.hpp"

namespace engine {
	class Color;
	class Shader;
	class Entity;
	class Object;
	class Mesh;
	class DebugObject;
	class Window;
	class Camera;

	struct RendererSpecs{
		/// Max and User Wanted Anisotropy Levels
		u32 mMaximumAnisotropy;	
		u32 mWantedAnisotropy;

		/// Max and User Wanted Anti-Aliasing Levels
		s16 mMaximumMultiSamples;
		s16 mWantedMultiSamples;

		/// BackFace Culling Face
		u32 mCullingFace;

		/// Field of View
		f32 mFOV;

		/// Near & Far plane
		f32 mNearPlane;
		f32 mFarPlane;

		/// Ambient Color
		Color mAmbientColor;

		/// Wireframe mode
		bool mWireframe;
		bool mWireframeChange;

		/// Vertical Synchronisation
		bool mVsync;
	};

    class OOXAPI Renderer : public Singleton<Renderer>{
        friend class Singleton<Renderer>;
    public:
        /// \brief Initialize the Renderer from Window
		/// \param pWindow : Window used to Render
        void Init(Window &pWindow);

        /// \brief Function called before rendering every frame
		/// \param pColor : Window background color
        void BeginScene(const Color &pColor) const;

        /// \brief Function called right after rendering every frame
        void EndScene();
		
		/// \brief Returns a pointer on the associated window
		const Window* GetWindow() { return mWindow; }

		/// \brief Returns the renderer specifications
		const RendererSpecs& GetSpecifications() const { return mSpecs; }

		// Functions used to render a drawable object with the renderer
			/// \brief Add a Mesh to the next frame drawing list
			void DrawMesh(Mesh* pEntity);
			
			/// \brief Add an Object to the next frame drawing list
			void DrawObject(Object* pEntity);
			
			/// \brief Add a DebugObject to the next frame drawing list
			void DrawDebugObject(DebugObject* pEntity);
			
			/// \brief Add a Text to the next frame drawing list
			void DrawText(Text* pText);


		/// \brief Render the drawable objects of the current frame
		void Render();

		/// \brief Change the Field of View
		void SetFOV(f32 pFov);

		/// \brief Change the Wireframe Mode
		void WireframeMode(bool pVal);

		/// \brief Resize the Window with the associated window new Width and Height
		void Resize();

		/// Matrix
			/// \brief Change the current 2D Projection Matrix
			void Set2DProjectionMatrix(const Matrix4 &pProj) { m2DProjectionMatrix = pProj; }
			
			/// \brief Change the current 3D Projection Matrix
			void Set3DProjectionMatrix(const Matrix4 &pProj) { m3DProjectionMatrix = pProj; }
			
			/// \brief Change the current 3D View Matrix. Changes also the ViewProj and Normal Matrices accordingly
			void Set3DViewMatrix(const Matrix4 &pView){ 
				m3DViewMatrix = pView; 
				m3DViewProjMatrix = m3DViewMatrix * m3DProjectionMatrix;
				m3DNormalMatrix = m3DViewMatrix.Inverse();
				m3DNormalMatrix = m3DNormalMatrix.Transpose();
			}

			/// Getters

			const Matrix4& Get2DProjectionMatrix() const { return m2DProjectionMatrix; }
			const Matrix4& Get3DProjectionMatrix() const { return m3DProjectionMatrix; }
			const Matrix4& Get3DViewProjMatrix() const { return m3DViewProjMatrix; }
			const Matrix4& Get3DNormalMatrix() const { return m3DNormalMatrix; }
			const Matrix4& Get3DViewMatrix() const { return m3DViewMatrix; }

		/// Camera
			/// \brief Set current camera from pointer
			void SetCamera(Camera* pCamera) { mCamera = pCamera; }

			/// \brief Returns a pointer on the current camera
			const Camera* GetCamera() const { return mCamera; }

    private:
		/// Private Ctor/Dtor (Singleton)
        Renderer();
        ~Renderer();

        /// Window
		Window* mWindow;
		u32 mWindowWidth, mWindowHeight;

		/// Camera
		Camera* mCamera;

		/// Specifications
		RendererSpecs mSpecs;

		/// Vector containing Objects to be drawn next frame
		typedef std::vector<Object*> ObjectMap;
		ObjectMap mObjectMap;
		ObjectMap::iterator mObjectMapIt;
		
		/// Vector containing Meshes to be drawn next frame
		typedef std::vector<Mesh*> MeshMap;
		MeshMap mMeshMap;
		MeshMap::iterator mMeshMapIt;

		/// Vector containing DebugObjects to be drawn next frame
		typedef std::vector<DebugObject*> DebugObjectMap;
		DebugObjectMap mDebugObjectMap;
		DebugObjectMap::iterator mDebugObjectMapIt;

		/// Number of drawed entities every frame
		Text mEntityNumberText;
		u16 mEntityNumber, mLastFrameEntityNumber;

		/// Vector containing Objects to be drawn next frame
		typedef std::vector<Text*> TextMap;
		TextMap mTextMap;
		TextMap::iterator mTextMapIt;

		/// Matrices used by the renderer
		Matrix4 m3DViewMatrix, m3DProjectionMatrix, m3DViewProjMatrix, m3DNormalMatrix;
		Matrix4 m2DProjectionMatrix;


		/// FUNCTIONS

		/// Specific drawable object rendering functions
			/// \brief Text Rendering
			void RenderTexts();

			/// \brief Objects Rendering
			void RenderObjects();

			/// \brief Meshes Rendering
			void RenderMeshes();

			/// \brief DebugObject Rendering
			void RenderDebugObjects();
    };
}
#endif
