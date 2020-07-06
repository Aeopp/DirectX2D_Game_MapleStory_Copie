#include "CCore.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLing,
	_In_ int nCmdShow) {

	if (!CCore::GetInst()->Init(hInstance)) {
		CCore::DestroyInst();
		return 0; 
	}

	int iRev = CCore::GetInst()->Run();

	// TODO :: Àç±Í ¼öÁ¤¿ä¸Á
	 DESTROY_SINGLE(CCore); 
	//  SAFE_DELETE(CCore); 
	//  CCore::DestroyInst();

	return iRev; 
}