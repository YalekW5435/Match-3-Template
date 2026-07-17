#include <PopLib/popapp.hpp>
#include <PopLib/widget/widgetmanager.hpp>
#include <PopLib/widget/widget.hpp>
#include <PopLib/graphics/color.hpp>
#include <PopLib/graphics/font.hpp>
#include <PopLib/graphics/graphics.hpp>
#define elif else if
namespace PopLib
{
	class WidgetManager;
	class Font;
	class Graphics;
	class Match3App;
	class LoadingDockObject;
	/*-----------------------------------------------------------------------------------------------------------------------*/
	/*-----------------------------------------------------------------------------------------------------------------------*/
	/*-----------------------------------------------------------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------------------------------------------------------*/
	/*-----------------------------------------------------------------------------------------------------------------------*/
	/*-----------------------------------------------------------------------------------------------------------------------*/
	class TitleScreen : public Widget
	{
	    private:
			
		   Match3App *mTheAppPtr;
		  LoadingDockObject *mTheObject;

		public:
			double mProgress;
			bool mLoadingCompleted;
		  float mTheX, mTheY, mTheVelocity;
		  float mTheLTX, mTheLTY;
		  double mTheSlowedProgressPercent;

		  
		  
		  
		  
		    int mProgressWidth;
			float mBGFadeInValue, mArcFadeInValue, mProgressFadeOutValue;
			
			Image *mLoadingDockImage, *mMainBackground, *mLoadArc, *mLoadRect;
			Rect mTheCurrentLoadingRectangle, mBackgroundSourceRect, mBackgroundDestinationRect;
			Color mTheImageFade;
			TitleScreen(Match3App *TheApp);
		    virtual ~TitleScreen();
			
			

			virtual void Init(void);
			virtual void Update();
			virtual void Draw(Graphics *PG);
		
	};

}