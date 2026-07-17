#include <PopLib/popapp.hpp>
#include <PopLib/appbase.hpp>
#include <PopLib/widget/widgetmanager.hpp>
#include <PopLib/widget/widget.hpp>
#include <PopLib/graphics/color.hpp>
#include <PopLib/graphics/font.hpp>
#include <PopLib/graphics/graphics.hpp>
#include <PopLib/math/matrix.hpp>

#include "TitleScreen.hpp"
#include "Assets.hpp"
#include "Match3App.hpp"
#include "LoadingDock.hpp"
using namespace PopLib;

TitleScreen::TitleScreen(Match3App* TheApp)
{ 
	//initialize our members as with every construct.
	mTheAppPtr = TheApp;
	mProgress = 0.00f;
	
	mTheX = 0;
	mTheY = 0;
	mTheVelocity = 0;
	mTheImageFade = 0;


	mLoadingDockImage = LoadDock;
	mLoadArc = LoadArc;
	/*------------------------------------------------------------------*/
	mMainBackground = MenuBackground;
	
	/*------------------------------------------------------------------*/
	
	mLoadRect = LoadingProgressImageRect;
	mBGFadeInValue = 0;
	mArcFadeInValue = 0;
	mTheLTX = 0;
	mTheLTY = 0;
	mTheCurrentLoadingRectangle = Rect(0, 0, 0, 0);
	mTheSlowedProgressPercent = 0.00;
	
	mBackgroundDestinationRect = Rect(0, 0, mMainBackground->mWidth * 0.5,
									  mMainBackground->mHeight * 0.5);
	mBackgroundSourceRect = Rect(0, 0, mMainBackground->mWidth,mMainBackground->mHeight);



}
TitleScreen::~TitleScreen()
{
	
}
void TitleScreen::Init(void)
{
	// leave empty unless if youre initializing a hyperlink widget...These widgets are only needed if you want a
	// "continue" button link, or the sorts.. since were not going to be using that, we are leaving this empty.
}

void TitleScreen::Update()
{
	//UPDATE INTEGER AND FLOAT VALUES HERE, NOT IMAGES!!
	Widget::Update();
	

	mProgress = mTheAppPtr->GetLoadingThreadProgress();
	//since we cant simulate the loading thread with a bar (its too fast)
	//we need to simulate it with a separate var to make it smaller.
	if (mTheSlowedProgressPercent < 1.0)
	{
		mTheSlowedProgressPercent += 0.00125;
	}
	if (mTheSlowedProgressPercent > 1.0)
	{
		
	    mTheSlowedProgressPercent = 1.0; // make the progress stay where it is.

	}
	MarkDirty();
	//Loading Dock Movement:
	mTheX = 0; //X Is zero because we dont need it.
	mTheY += 3.25;// This is the velocity variable.  

	//The following if statement provides where the loading dock thing should stop.  Notice, it stopped at a different coordinate than y = 900, (it touched the ring image).
	//Why?  Because, we want it to stop after 900 ticks since mTheY was initialized at the corrdinate 1200.  This means it is moving from 1200, 
	// to coordinate 100.  Because 1200 - 900 = 100.  So, by providing mTheY >= 900, it stops there at 100, therefore touching the ring image as seen in
	//Bejeweled twist.  

	if (mTheY >= 900)
	{

		mTheY = 900;
	}
	
	//PLEASE MARK THIS DIRTY, OR IT WILL NOT MOVE!  AKA REPAINT.
	
	MarkDirty();
	//Allows for fading in the background.  
	if (mBGFadeInValue < 255.0f)
	{
		mBGFadeInValue += 0.51f;//Note: if this value is a tad low, please increase this to have faster alpha rendering.
	}
	MarkDirty();
	
	//Fade in the arc.  This is going to be a tad bit slower because we arent using mProgress.
	if (mArcFadeInValue < 255.0f)
	{

		mArcFadeInValue += 3.75f;
	}

	mProgressWidth = (int)(mTheSlowedProgressPercent * mLoadRect->mWidth);
	mTheCurrentLoadingRectangle = Rect(0, 0, mProgressWidth, mLoadRect->mHeight);
	
	
	
}

void TitleScreen::Draw(Graphics* PG)
{
	
	PG->SetDrawMode(1);//additive draw mode for additional processing.
	PG->FillRect(0, 0, mWidth, mHeight);

	/*-----------------------------------------------------------------------------------------------*/
	PG->SetColor(Color(255, 255, 255, (int)mBGFadeInValue));

	PG->SetColorizeImages(true);

	PG->DrawImage(mMainBackground, mBackgroundDestinationRect, mBackgroundSourceRect);
	
	
	PG->SetColorizeImages(false);
	
	MarkDirty();
/*-----------------------------------------------------------------------------------------------*/
	//Now lets do the arc/ring.  Again, follow the same angle.  
/*-----------------------------------------------------------------------------------------------*/
	PG->SetColor(Color(255, 255, 255, (int)mArcFadeInValue));
	PG->SetColorizeImages(true);
	PG->DrawImage(mLoadArc, 457.5, 32.5);
	PG->SetColorizeImages(false);
	MarkDirty();
	/*-----------------------------------------------------------------------------------------------*/
	//And now the loadRect, with additive drawing.
	/*-----------------------------------------------------------------------------------------------*/
	PG->SetDrawMode(1);
	
	PG->DrawImage(mLoadRect, 535, 606.5, mTheCurrentLoadingRectangle);
	
	if (mProgressWidth >= 520)
	{
		//clear the rectangle since we already have the thing made, including the load arc.
		//And start preparing the loading dock ship thingy for launch.  WIP.

		mLoadRect->ClearRect(mTheCurrentLoadingRectangle);
		mLoadArc->ClearRect(Rect(0,0, mLoadArc->mWidth, mLoadArc->mHeight));
		mLoadingDockImage->ClearRect(Rect(0, 0, mLoadingDockImage->mWidth, mLoadingDockImage->mHeight));
		
		
		
	}
	PG->DrawImage(mLoadingDockImage, 375, 1200 - (mTheY += mTheVelocity));
	MarkDirty();

	

	/*-----------------------------------------------------------------------------------------------*/
	// you may have noticed both the load dock AND arc dissappeared, this still needs work.  Idk what will become of it, as I have other
	//things to do.  Hope you enjoyed!
}
