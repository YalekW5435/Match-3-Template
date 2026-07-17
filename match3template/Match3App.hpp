#include <PopLib/appbase.hpp>
#include <PopLib/popapp.hpp>
#include <PopLib/resources/resourcemanager.hpp>
#include <PopLib/widget/WidgetManager.hpp>
#include <PopLib/graphics/color.hpp>

namespace PopLib

{

class Canvas;
class ResourceManager;
class Color;
class TitleScreen;
class Graphics;
class WidgetManager;
class LoadingDockObject;
class Match3App : public PopApp

	{
  private:
	TitleScreen *mTitleScreen;
	Canvas *mTheCanvas;

  public:


	  Match3App();
		virtual ~Match3App();

		virtual void InitHook();
		virtual void LoadingThreadProc();
	   virtual void LoadingThreadCompleted();
		




	};

}