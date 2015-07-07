////////////////////////////////////////////////////////////
/// \mainpage
///
/// \section welcome 00xEngine Index Page
/// Welcome to the official 00xEngine documentation. 
/// Some links :
/// - Description of all 00xEngine <a href="./annotated.htm">classes</a>.
/// - Description of all 00xEngine <a href="./files.htm">files</a>. <br>
///
/// \section example Short example
/// This is a minimum-code/simple example of how to use the engine :
///
/// \code
///
/// #include "Engine.hpp"
/// 
/// using namespace engine;
///
/// int main(){
///     // Initialize Loggers (used for debug)
///     ILogger::Init();
///
///		// Parse the config file (default is Options.cfg)
///		Settings::Call().Parse();
///
///		// Add Paths for the ResourceManager to find resources
///		ResourceManager::Call().AddPath("Data/shaders", "Shader");
///		ResourceManager::Call().AddPath("Data/textures", "Image");
///
///		{
///			// Create our window
///			Window myWindow;
///			
///			// Retrieve the engine Renderer and initialize it with our window
///			Renderer& myRenderer = Renderer::Call();
///			myRenderer.Init(myWindow);
///
///			// Create our inputs and initialize it with our window
///			Input myInput;
///			myInput.Init(myWindow);
///
///			// Make some text
///			Text myText;
///			myText.SetText("00xEngine");
///			myText.SetPosition(320, 260);
///
///
///			// Begin Main Loop
///			while(myWindow.IsOpened()){
///				// Retrieve frame events
///				while(myInput.GetEvent()){
///					// Look if the window Close Event happens, if so, close the window
///					if(myInput.GetEventType() == sf::Event::Closed)
///						myWindow.Close();
///				}
///
///				// Draw our text
///				myText.Draw();
///
///				// Begin the rendering with some background color
///				myRenderer.BeginScene(Color::Black);
///					// Render the scene
///					myRenderer.Render();
///				// End the rendering
///				myRenderer.EndScene();
///			}
///		}
///
///		// Destroy some instances
///		Renderer::Kill();
///		ResourceManager::Kill();
///		Settings::Kill();
///		ILogger::Kill();
///		MemoryManager::Kill();
/// }
/// 
/// \endcode
////////////////////////////////////////////////////////////
