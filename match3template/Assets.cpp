#include "Assets.hpp"
#include "PopLib/resources/resourcemanager.hpp"

using namespace PopLib;

#pragma warning(disable:4311 4312)

static bool gNeedRecalcVariableToIdMap = false;

bool PopLib::AssetsExtractResourcesByName(ResourceManager *theManager, const char *theName)
{
	if (strcmp(theName,"Main")==0) return AssetsExtractMainResources(theManager);
	return false;
}

PopLib::AssetsResourceId PopLib::AssetsGetIdByStringId(const char *theStringId)
{
	typedef std::map<std::string,int> MyMap;
	static MyMap aMap;
	if(aMap.empty())
	{
		for(int i=0; i<AssetsRESOURCE_ID_MAX; i++)
			aMap[AssetsGetStringIdById(i)] = i;
	}

	MyMap::iterator anItr = aMap.find(theStringId);
	if (anItr == aMap.end())
		return AssetsRESOURCE_ID_MAX;
	else
		return (AssetsResourceId) anItr->second;
}

// Main Resources
Image* PopLib::Amber;
Font* PopLib::BoardScoreFontL1;
Font* PopLib::BoardScoreFontL2;
Font* PopLib::BoardScoreFontL3;
Image* PopLib::ButtonPod1;
Image* PopLib::ButtonPod2;
Image* PopLib::ButtonPod3;
Image* PopLib::ButtonPod4;
Image* PopLib::ButtonPod5;
Image* PopLib::Emerald;
Image* PopLib::GridSurface;
Image* PopLib::LoadArc;
Image* PopLib::LoadDock;
Image* PopLib::LoadingBeam;
Image* PopLib::LoadingProgressImageRect;
Image* PopLib::Menu;
Image* PopLib::MenuBackground;
Image* PopLib::Ruby;
Image* PopLib::Sapphire;
Image* PopLib::TheLaserBeam;
Image* PopLib::Topaz;
Font* PopLib::TotalScoreFont;
Font* PopLib::UIFont;
Image* PopLib::Violet;
Image* PopLib::White;
Image* PopLib::score1;
Image* PopLib::score2;

bool PopLib::AssetsExtractMainResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		Amber = aMgr.GetImageThrow("Amber");
		BoardScoreFontL1 = aMgr.GetFontThrow("BoardScoreFontL1");
		BoardScoreFontL2 = aMgr.GetFontThrow("BoardScoreFontL2");
		BoardScoreFontL3 = aMgr.GetFontThrow("BoardScoreFontL3");
		ButtonPod1 = aMgr.GetImageThrow("ButtonPod1");
		ButtonPod2 = aMgr.GetImageThrow("ButtonPod2");
		ButtonPod3 = aMgr.GetImageThrow("ButtonPod3");
		ButtonPod4 = aMgr.GetImageThrow("ButtonPod4");
		ButtonPod5 = aMgr.GetImageThrow("ButtonPod5");
		Emerald = aMgr.GetImageThrow("Emerald");
		GridSurface = aMgr.GetImageThrow("GridSurface");
		LoadArc = aMgr.GetImageThrow("LoadArc");
		LoadDock = aMgr.GetImageThrow("LoadDock");
		LoadingBeam = aMgr.GetImageThrow("LoadingBeam");
		LoadingProgressImageRect = aMgr.GetImageThrow("LoadingProgressImageRect");
		Menu = aMgr.GetImageThrow("Menu");
		MenuBackground = aMgr.GetImageThrow("MenuBackground");
		Ruby = aMgr.GetImageThrow("Ruby");
		Sapphire = aMgr.GetImageThrow("Sapphire");
		TheLaserBeam = aMgr.GetImageThrow("TheLaserBeam");
		Topaz = aMgr.GetImageThrow("Topaz");
		TotalScoreFont = aMgr.GetFontThrow("TotalScoreFont");
		UIFont = aMgr.GetFontThrow("UIFont");
		Violet = aMgr.GetImageThrow("Violet");
		White = aMgr.GetImageThrow("White");
		score1 = aMgr.GetImageThrow("score1");
		score2 = aMgr.GetImageThrow("score2");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

static void* gResources[] =
{
	&LoadDock,
	&LoadArc,
	&LoadingProgressImageRect,
	&MenuBackground,
	&LoadingBeam,
	&TheLaserBeam,
	&Menu,
	&score1,
	&score2,
	&ButtonPod1,
	&ButtonPod2,
	&ButtonPod3,
	&ButtonPod4,
	&ButtonPod5,
	&GridSurface,
	&Amber,
	&Emerald,
	&Ruby,
	&Sapphire,
	&Topaz,
	&Violet,
	&White,
	&TotalScoreFont,
	&UIFont,
	&BoardScoreFontL1,
	&BoardScoreFontL2,
	&BoardScoreFontL3,
	NULL
};

Image* PopLib::AssetsLoadImageById(ResourceManager *theManager, int theId)
{
	return (*((Image**)gResources[theId]) = theManager->LoadImage(AssetsGetStringIdById(theId)));
}

void PopLib::AssetsReplaceImageById(ResourceManager *theManager, int theId, Image *theImage)
{
	theManager->ReplaceImage(AssetsGetStringIdById(theId),theImage);
	*(Image**)gResources[theId] = theImage;
}

Image* PopLib::AssetsGetImageById(int theId)
{
	return *(Image**)gResources[theId];
}

Font* PopLib::AssetsGetFontById(int theId)
{
	return *(Font**)gResources[theId];
}

int PopLib::AssetsGetSoundById(int theId)
{
	return *(int*)gResources[theId];
}

Image*& PopLib::AssetsGetImageRefById(int theId)
{
	return *(Image**)gResources[theId];
}

Font*& PopLib::AssetsGetFontRefById(int theId)
{
	return *(Font**)gResources[theId];
}

int& PopLib::AssetsGetSoundRefById(int theId)
{
	return *(int*)gResources[theId];
}

static PopLib::AssetsResourceId AssetsGetIdByVariable(const void *theVariable)
{
	typedef std::map<int,int> MyMap;
	static MyMap aMap;
	if(gNeedRecalcVariableToIdMap)
	{
		gNeedRecalcVariableToIdMap = false;
		aMap.clear();
		for(int i=0; i<AssetsRESOURCE_ID_MAX; i++)
			aMap[*(int*)gResources[i]] = i;
	}

	MyMap::iterator anItr = aMap.find((int)theVariable);
	if (anItr == aMap.end())
		return AssetsRESOURCE_ID_MAX;
	else
		return (AssetsResourceId) anItr->second;
}

PopLib::AssetsResourceId PopLib::AssetsGetIdByImage(Image *theImage)
{
	return AssetsGetIdByVariable(theImage);
}

PopLib::AssetsResourceId PopLib::AssetsGetIdByFont(Font *theFont)
{
	return AssetsGetIdByVariable(theFont);
}

PopLib::AssetsResourceId PopLib::AssetsGetIdBySound(int theSound)
{
	return AssetsGetIdByVariable((void*)theSound);
}

const char* PopLib::AssetsGetStringIdById(int theId)
{
	switch(theId)
	{
		case LoadDock_ID: return "LoadDock";
		case LoadArc_ID: return "LoadArc";
		case LoadingProgressImageRect_ID: return "LoadingProgressImageRect";
		case MenuBackground_ID: return "MenuBackground";
		case LoadingBeam_ID: return "LoadingBeam";
		case TheLaserBeam_ID: return "TheLaserBeam";
		case Menu_ID: return "Menu";
		case score1_ID: return "score1";
		case score2_ID: return "score2";
		case ButtonPod1_ID: return "ButtonPod1";
		case ButtonPod2_ID: return "ButtonPod2";
		case ButtonPod3_ID: return "ButtonPod3";
		case ButtonPod4_ID: return "ButtonPod4";
		case ButtonPod5_ID: return "ButtonPod5";
		case GridSurface_ID: return "GridSurface";
		case Amber_ID: return "Amber";
		case Emerald_ID: return "Emerald";
		case Ruby_ID: return "Ruby";
		case Sapphire_ID: return "Sapphire";
		case Topaz_ID: return "Topaz";
		case Violet_ID: return "Violet";
		case White_ID: return "White";
		case TotalScoreFont_ID: return "TotalScoreFont";
		case UIFont_ID: return "UIFont";
		case BoardScoreFontL1_ID: return "BoardScoreFontL1";
		case BoardScoreFontL2_ID: return "BoardScoreFontL2";
		case BoardScoreFontL3_ID: return "BoardScoreFontL3";
		default: return "";
	}
}

