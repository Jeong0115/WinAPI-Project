//#include "zzkirbyComponent.h"
//#include "zzResourceMgr.h"
//#include "zzTime.h"
//#include "zzKirby.h"
//#include "zzEngine.h"
//#include "zzKey.h"
//
//namespace zz
//{
//	kirbyComponent::kirbyComponent()
//		: idx(0)
//		, sec(0.f)
//		, bPress(false)
//	{
//	}
//	kirbyComponent::~kirbyComponent()
//	{
//	}
//	void kirbyComponent::Initialize()
//	{
//		icy.push_back(ResourceMgr::Load<Texture>(L"ice_1", L"..\\Resources\\images\\Ice-Kirby_1.bmp"));
//		icy.push_back(ResourceMgr::Load<Texture>(L"ice_2", L"..\\Resources\\images\\Ice-Kirby_2.bmp"));
//		icy.push_back(ResourceMgr::Load<Texture>(L"ice_3", L"..\\Resources\\images\\Ice-Kirby_3.bmp"));
//		icy.push_back(ResourceMgr::Load<Texture>(L"ice_4", L"..\\Resources\\images\\Ice-Kirby_4.bmp"));
//		icy.push_back(ResourceMgr::Load<Texture>(L"ice_5", L"..\\Resources\\images\\Ice-Kirby_5.bmp"));
//		icy.push_back(ResourceMgr::Load<Texture>(L"ice_6", L"..\\Resources\\images\\Ice-Kirby_6.bmp"));
//		icy.push_back(ResourceMgr::Load<Texture>(L"ice_7", L"..\\Resources\\images\\Ice-Kirby_7.bmp"));
//		icy.push_back(ResourceMgr::Load<Texture>(L"ice_8", L"..\\Resources\\images\\Ice-Kirby_8.bmp"));
//		icy.push_back(ResourceMgr::Load<Texture>(L"ice_9", L"..\\Resources\\images\\Ice-Kirby_9.bmp"));
//		icy.push_back(ResourceMgr::Load<Texture>(L"ice_10", L"..\\Resources\\images\\Ice-Kirby_10.bmp"));
//		icy.push_back(ResourceMgr::Load<Texture>(L"ice_11", L"..\\Resources\\images\\Ice-Kirby_11.bmp"));
//		icy.push_back(ResourceMgr::Load<Texture>(L"ice_12", L"..\\Resources\\images\\Ice-Kirby_12.bmp"));
//		icy.push_back(ResourceMgr::Load<Texture>(L"ice_13", L"..\\Resources\\images\\Ice-Kirby_13.bmp"));
//		icy.push_back(ResourceMgr::Load<Texture>(L"ice_14", L"..\\Resources\\images\\Ice-Kirby_14.bmp"));
//
//		ice = icy[0];
//	}
//	void kirbyComponent::Update()
//	{
//		bPress = false;
//		if (KEY(X, PRESSED))
//		{
//			bPress = true;
//		}
//		sec += Time::DeltaTime();
//		if(sec>0.08f)
//		{
//			ice = icy[idx];
//			idx++;
//			if (idx >= icy.size()) idx = 0;
//			sec = 0.f;
//		}
//	}
//
//	void kirbyComponent::Render(HDC hdc, Vector2 pos)
//	{
//		
//		if(bPress)
//		{
//			TransparentBlt(hdc, pos.x + 15, pos.y - 10, ice->GetWidth(),
//				ice->GetHeight(), ice->GetHdc(), 0, 0,
//				ice->GetWidth(), ice->GetHeight(), RGB(0, 0, 255));
//		}
//	}
//
//	void kirbyComponent::Release()
//	{
//
//	}
//}