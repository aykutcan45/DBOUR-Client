/*****************************************************************************
 *
 * File			: ChatGui.h
 * Author		: Peessi
 * Copyright	: (��)NTL
 * Date			: 2007. 5. 10	
 * Abstract		: DBO chatting gui.
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __CHAT_GUI_H__
#define __CHAT_GUI_H__

#include "NtlPLGui.h"
#include "SurfaceGui.h"
#include "ceventhandler.h"
#include "Windowby3.h"
#include "ChatDefine.h"


class CChatOptionGui;
class CChatDisplayGui;
class CChatReceiver;
class CChatSender;

//

class CChatGui : public CNtlPLGui , public RWS::CEventHandler
{
public:
	typedef std::list<CChatDisplayGui*>					LIST_DISPLAY_GUI;

	struct sChatOption
	{
		RwBool				bAlwaysInput;				///< ä���Է��� �Է¸�尡 �����Ǵ��� ����
		bool				bLockChatDisplay;
		bool				bShowChatScroll;
		RwUInt8				byAlpha;
	};

	struct sPositionInfo
	{
		RwInt32				iOldScreenHeight;			///< Ŭ���̾�Ʈ Resize�� �ϴܿ��� ������ �Ÿ� ���� ����
	};


	//! Constructor & Destructor	
	CChatGui( const RwChar* pName );
	~CChatGui(VOID);

	//! Operation
	RwBool	Create(VOID);
	VOID	Destroy(VOID);

	RwInt32 SwitchDialog(bool bOpen);
	RwInt32 ActionMapTabKey(VOID);
	RwInt32 ActionMapChangeTab(RwUInt32 uiOption);

	RwBool	IsFocused(VOID);

	VOID	FocusToInput(VOID);

	VOID	ShowChatButton(eChatType eType, bool bShow);

	VOID	SetChatType( eChatType eType );
	eChatType GetChatType();

	VOID	SetLastRecieveWhisperName(WCHAR* pwcName);
	std::wstring& GetLastRecieveWhisperName(VOID) { return m_wstrLastRecieveWhisterName; }

	CChatReceiver*	GetReceiver() { return m_pChatReceiver; }

	VOID	SetDismovableDisplayPositioin(RwBool bForce = FALSE);
	
	//! Event
	virtual VOID HandleEvents( RWS::CMsg& msg );

private:
	CChatGui(VOID) {}

	RwBool	AddDisplayGui();
	VOID	RemoveDisplayGui(RwUInt8 byDisplayIndex);	
	VOID	ShowChatGui(bool bShow);
	VOID	SetComponentPosition();

	// Chat option
	VOID	Option_AlwaysInput(bool bEnable);
	VOID	Option_LockChatDisplay(bool bEnable);
	VOID	Option_MoreDisplayGui();
	VOID	Option_LessDisplayGui();
	VOID	Option_Alpha(RwUInt8 byAlpha);
	VOID	Option_DisplayChatLogType(RwUInt8 byDisplayIndex, eChatType eType, RwBool bEnable);

	// Option_DisplayChatLogType �Լ��� ��� ȣ���� �ڿ� �� ����� �����ϱ� ���� �Լ�
	VOID	Option_RefreshDisplayChatLog(RwUInt8 byDisplayIndex);

	//! Callbacks
	VOID	OnGotFocus(VOID);
	VOID	OnLostFocus(VOID);
	VOID	OnInputReturn(VOID);
	VOID	OnOptionButton( gui::CComponent* pComponent );	
	VOID	OnChatTypeButton( gui::CComponent* pComponent );
	VOID	OnModeSelBtnClick( gui::CComponent* pComponent );
	VOID	OnMove( RwInt32 nOldX, RwInt32 nOldY );
	VOID	OnResize( RwInt32 iOldW, RwInt32 iOldH );
	VOID	OnIMEChange( INT eIMEState );
	VOID	OnESCKeyUp(VOID);
	VOID	OnPaint(VOID);

protected:
	gui::CSlot	m_slotGotFocus;
	gui::CSlot	m_slotLostFocus;
	gui::CSlot	m_slotReturn;
	gui::CSlot	m_slotOption;
	gui::CSlot	m_slotChatButton[NUM_NET_CHAT_TYPE];
	gui::CSlot	m_slotModeSelBtnClick;
	gui::CSlot	m_slotMove;
	gui::CSlot	m_slotResize;
	gui::CSlot  m_slotIMEChange;
	gui::CSlot	m_slotESCKeyUp;
	gui::CSlot	m_slotPaint;

	gui::CDialog*		m_pManagerDialog;
	gui::CButton*		m_pSelBtn;
	gui::CButton*		m_pOptionBtn;
	gui::CButton*		m_pChatTypeButton[NUM_NET_CHAT_TYPE];
	gui::CPanel*		m_pChatTypePanel[NUM_NET_CHAT_TYPE];
	gui::CStaticBox*	m_pIME;
	gui::CInputBox*		m_pInput;
	
	CWindowby3			m_InputBackground;

	//! Variables
	LIST_DISPLAY_GUI	m_listDisplayGui;
	CChatOptionGui*		m_pChatOptionGui;	
	CChatReceiver*		m_pChatReceiver;
	CChatSender*		m_pSender;

	std::wstring		m_wstrLastRecieveWhisterName; // �ֱ� �ӼӸ��� ���� ��������.

	RwBool				m_bChatModeEndReturn;
	RwBool				m_bRenderBackground;
	RwBool				m_bInitializedOption;			/// �ɼǿ� ���� �ʱ�ȭ�� �ߴ�
	eChatType			m_eChatType;
	sChatOption			m_ChatOption;
	sPositionInfo		m_tPositionInfo;	
};

#endif