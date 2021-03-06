#include "gui_precomp.h"
#include "gui_particle_doc.h"
#include "gui_particlepath.h"
#include "NtlDebug.h"

#include "GuiUtil.h"
#include <string>

#include "gui_componenttokenizer.h"

START_GUI

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CValueItem

CValueItem::CValueItem()
{
}

CValueItem::~CValueItem()
{

}

/**
* \brief 파티클 아이템이 키와 자료값으로 가진 데이터를 추가한다. 기존에 키 값을 가지고 있으면 덮어쓴다.
* \param strKey		(std::string) 키
* \param strValue	(std::string) 자료값
* \return TRUE : 존재함 FALSE : 존재하지 않음
*/
BOOL CValueItem::AddValue( std::string strKey, std::string strValue )
{
	VALUEMAP::iterator it = m_mapValue.find( strKey );

	// 없으면 추가하고
	if( it == m_mapValue.end() )
	{
		m_mapValue.insert( make_pair( strKey, strValue ) );

		return TRUE;
	}
	// 있다면 덮어 쓴다.
	else
	{
		(*it).second = strValue;

		return FALSE;
	}
}

BOOL CValueItem::AddValue( std::string strKey, int nValue )
{
	char acBuffer[256];
	sprintf_s( acBuffer, 256, "%d", nValue );
	
	return AddValue( strKey, acBuffer );
}

BOOL CValueItem::AddValue( std::string strKey, float fValue )
{
	char acBuffer[256];
	sprintf_s( acBuffer, 256, "%f", fValue );

	return AddValue( strKey, acBuffer );
}
/**
* \brief 파티클 아이템의 키값으로 그 값을 지워버린다.
* \param strKey		(std::string) 키 값
* \return TRUE : 존재함 FALSE : 존재하지 않음
*/
BOOL CValueItem::RemoveValue( std::string strKey )
{
	VALUEMAP::iterator it = m_mapValue.find( strKey );

	if( it != m_mapValue.end() )
	{
		m_mapValue.erase( it );

		return TRUE;
	}
	else
		return FALSE;
}

/**
* \brief 키를 찾아서 값을 가지고 온다.
* \param strKey		(std::string) 찾을 키
* \param nValue		(int&) 저장될 변수
* \return 성공여부
*/
BOOL CValueItem::GetValue( std::string strKey, int& nValue )
{
	VALUEMAP::iterator it = m_mapValue.find( strKey );
	if( it != m_mapValue.end() )
	{
		nValue = atoi( ((*it).second).c_str() );

		return TRUE;
	}
	
	return FALSE;
}

BOOL CValueItem::GetValue( std::string strKey, RwV2d& v2dValue )
{
	char buf[256];
	char token[256];

	VALUEMAP::iterator it = m_mapValue.find( strKey );
	if( it != m_mapValue.end() )
	{
		sprintf_s( buf, 256, "%s", ((*it).second).c_str() );

		ExtractTokenByLastChar( buf, token, sizeof(token), "(" );
		ExtractTokenByLastChar( buf, token, sizeof(token), "," ); v2dValue.x = (float)atof( token );
		ExtractTokenByLastChar( buf, token, sizeof(token), ")" ); v2dValue.y = (float)atof( token );

		return TRUE;
	}

	return FALSE;
}

BOOL CValueItem::GetValue( std::string strKey, float& fValue )
{
	VALUEMAP::iterator it = m_mapValue.find( strKey );
	if( it != m_mapValue.end() )
	{
		fValue = (float)atof( ((*it).second).c_str() );

		return TRUE;
	}

	return FALSE;
}

BOOL CValueItem::GetValue( std::string strKey, RwRGBA& colorValue )
{
	char buf[256];
	char token[256];

	VALUEMAP::iterator it = m_mapValue.find( strKey );
	if( it != m_mapValue.end() )
	{
		sprintf_s( buf, 256, "%s", ((*it).second).c_str() );

		ExtractTokenByLastChar( buf, token, sizeof(token), "(" );
		ExtractTokenByLastChar( buf, token, sizeof(token), "," ); colorValue.red = (unsigned char)atoi( token );
		ExtractTokenByLastChar( buf, token, sizeof(token), "," ); colorValue.green = (unsigned char)atoi( token );
		ExtractTokenByLastChar( buf, token, sizeof(token), "," ); colorValue.blue = (unsigned char)atoi( token );
		ExtractTokenByLastChar( buf, token, sizeof(token), ")" ); colorValue.alpha = (unsigned char)atoi( token );

		return TRUE;
	}

	return FALSE;
}

BOOL CValueItem::GetValue( std::string strKey, float& fValue1, float& fValue2 )
{
	char buf[256];
	char token[256];

	VALUEMAP::iterator it = m_mapValue.find( strKey );
	if( it != m_mapValue.end() )
	{
		sprintf_s( buf, 256, "%s", ((*it).second).c_str() );

		ExtractTokenByLastChar( buf, token, sizeof(token), "(" );
		ExtractTokenByLastChar( buf, token, sizeof(token), "," ); fValue1 = (float)atof( token );
		ExtractTokenByLastChar( buf, token, sizeof(token), ")" ); fValue2 = (float)atof( token );

		return TRUE;
	}

	return FALSE;
}

BOOL CValueItem::GetValue( std::string strKey, int& nValue1, int& nValue2 )
{
	char buf[256];
	char token[256];

	VALUEMAP::iterator it = m_mapValue.find( strKey );
	if( it != m_mapValue.end() )
	{
		sprintf_s( buf, 256, "%s", ((*it).second).c_str() );

		ExtractTokenByLastChar( buf, token, sizeof(token), "(" );
		ExtractTokenByLastChar( buf, token, sizeof(token), "," ); nValue1 = atoi( token );
		ExtractTokenByLastChar( buf, token, sizeof(token), ")" ); nValue2 = atoi( token );

		return TRUE;
	}

	return FALSE;
}

BOOL CValueItem::GetValue( std::string strKey, unsigned char& uValue1, unsigned char& uValue2, unsigned char& uValue3, unsigned char& uValue4 )
{
	char buf[256];
	char token[256];

	VALUEMAP::iterator it = m_mapValue.find( strKey );
	if( it != m_mapValue.end() )
	{
		sprintf_s( buf, 256, "%s", ((*it).second).c_str() );

		ExtractTokenByLastChar( buf, token, sizeof(token), "(" );
		ExtractTokenByLastChar( buf, token, sizeof(token), "," ); uValue1 = (unsigned char)atoi( token );
		ExtractTokenByLastChar( buf, token, sizeof(token), "," ); uValue2 = (unsigned char)atoi( token );
		ExtractTokenByLastChar( buf, token, sizeof(token), "," ); uValue3 = (unsigned char)atoi( token );
		ExtractTokenByLastChar( buf, token, sizeof(token), ")" ); uValue4 = (unsigned char)atoi( token );

		return TRUE;
	}

	return FALSE;
}

BOOL CValueItem::GetValue( std::string strKey, std::string& strValue )
{
	VALUEMAP::iterator it = m_mapValue.find( strKey );
	if( it != m_mapValue.end() )
	{
		char buf[256];
		sprintf_s( buf, 256, "%s", ((*it).second).c_str() );
		strValue = buf;

		return TRUE;
	}

	return FALSE;
}

BOOL CValueItem::GetValue( std::string strKey, unsigned char& uValue )
{
	VALUEMAP::iterator it = m_mapValue.find( strKey );
	if( it != m_mapValue.end() )
	{
		uValue = (unsigned char)atoi( ((*it).second).c_str() );

		return TRUE;
	}

	return FALSE;
}

BOOL CValueItem::GetValue( std::string strKey, char* pBuffer, int nBufferSize )
{
	VALUEMAP::iterator it = m_mapValue.find( strKey );
	if( it != m_mapValue.end() )
	{
		if( nBufferSize > (int)strlen( ((*it).second).c_str() ) )
		{
			memcpy( pBuffer,((*it).second).c_str(), sizeof(char) * strlen( ((*it).second).c_str() ) );

			return TRUE;
		}
	}

	return FALSE;

}

BOOL CValueItem::GetValue( std::string strKey, SCtrlPoint* pBuffer, int nBufferSize )
{
	char buf[4096];
	char token[256];

	VALUEMAP::iterator it = m_mapValue.find( strKey );
	if( it != m_mapValue.end() )
	{
		sprintf_s( buf, 4096, "%s", ((*it).second).c_str() );

		for( int i = 0; i < nBufferSize; ++i )
		{
			ExtractTokenByLastChar( buf, token, sizeof(token), "(" );
			ExtractTokenByLastChar( buf, token, sizeof(token), "," ); pBuffer[i].vPos.x = (float)atof( token );
			ExtractTokenByLastChar( buf, token, sizeof(token), "," ); pBuffer[i].vPos.y = (float)atof( token );
			ExtractTokenByLastChar( buf, token, sizeof(token), ")" ); pBuffer[i].fTime = (float)atof( token );
		}

		return TRUE;
	}

	return FALSE;
}
/**
* \brief 현재의 클래스의 이름을 지정한다.
* \param strName		(std::string) 이름
*/
void CValueItem::SetName( std::string strName )
{
	m_strName = strName;
}

/**
* \brief 현재의 클래스의 타입을 지정한다.
* \param strType		(std::string) 타입
*/
void CValueItem::SetType( std::string strType )
{
	m_strType = strType;
}

/**
* \brief 이름 리턴
*/
std::string CValueItem::GetName()
{
	return m_strName;
}

/**
* \brief 타입 리턴
*/
std::string CValueItem::GetType()
{	
	return m_strType;
}

/**
* \brief 이 클래스가 가지고 있는 자료의 갯수를 리턴
*/
int CValueItem::GetSize()
{
	return (int)m_mapValue.size();
}

void CValueItem::Clear()
{
	m_mapValue.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CParticleItem

/**
* \brief Construction
*/
CParticleItem::CParticleItem()
{
	// 기본적으로 ValueItem에 초기화 될 값들을 지정해준다.

	// Emitter
	m_itemValue[ITEM_EMITTER].SetName( "point" );
	m_itemValue[ITEM_EMITTER].SetType( "emitter" );
}

/**
* \brief Destruction
*/
CParticleItem::~CParticleItem()
{

}
/**
* \brief 파티클의 이름을 지정한다.
* \param strName	(std::string) 파티클의 이름
*/
void CParticleItem::SetName( std::string strName )
{
	m_strName = strName;
}

/**
* \brief 파티클의 이름을 리턴한다.
*/
std::string CParticleItem::GetName()
{
	return m_strName;
}

/**
* \brief 파티클에 값을 추가한다.
* \param eType		(eItemType) CValueItem 의 타입
* \param strKey		(strKey) 키값
* \param strValue	(strValue) 값
* \return 존재했나 안했나의 여부
*/
BOOL CParticleItem::AddValue( eItemType eType, std::string strKey, std::string strValue )
{
	if( eType > ITEM_NUMS )
		return FALSE;

	return m_itemValue[eType].AddValue( strKey, strValue );
}

/**
* \brief 파티클에 키를 제거한다.
* \param eType		(eItemType) CValueItem 의 타입
* \param strKey		(std::string) 파티클의 키
* \return 성공여부
*/
BOOL CParticleItem::RemoveValue( eItemType eType, std::string strKey )
{
	if( eType > ITEM_NUMS )
		return FALSE;
	
	return m_itemValue[eType].RemoveValue( strKey );
}

/**
* \brief 타입에 따른 ValueItem을 리턴
* \param eItemType		(eType)
* \return CValueItem*
*/
CValueItem* CParticleItem::GetValueItem( eItemType eType )
{
	if( eType > ITEM_NUMS )
		return NULL;

	return &m_itemValue[eType];
}


/**
* \brief 타입에 따른 ValueItem에 이름을 정한다.
* \param eType		(eItemType) CValueItem의 종류
* \param strName	(std::string) 이름
*/
BOOL CParticleItem::SetValueItemName( eItemType eType, std::string strName )
{
	if( eType > ITEM_NUMS )
		return FALSE;

	m_itemValue[eType].SetName( strName );

	return TRUE;
}

BOOL CParticleItem::SetValueItemType( eItemType eType, std::string strType )
{
	if( eType > ITEM_NUMS )
		return FALSE;

	m_itemValue[eType].SetType( strType );

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CParticleGroup

CParticleGroup::CParticleGroup()
{
	m_itCurrent = m_mapParticle.end();
}

CParticleGroup::~CParticleGroup()
{
	MAPPARTICLEIT it = m_mapParticle.begin();
	while( it != m_mapParticle.end() )
	{
		NTL_DELETE( (*it).second );
		++it;
	}
	m_mapParticle.clear();
}

std::string CParticleGroup::GetName()
{
	return m_strGroupName;
}

void CParticleGroup::SetName( std::string strName )
{
	m_strGroupName = strName;
}

int CParticleGroup::GetSize()
{
	return (int)m_mapParticle.size();
}

CParticleItem* CParticleGroup::AddParticle( const char* parname )
{
	MAPPARTICLEIT it = m_mapParticle.find( parname );
	if( it == m_mapParticle.end() )
	{
		CParticleItem* pItem = NTL_NEW CParticleItem;
		pItem->SetName( parname );
		m_mapParticle.insert( std::make_pair( parname, pItem ) );
		
		return pItem;
	}

	return NULL;
}

CParticleItem* CParticleGroup::GetParticle( const char* parname )
{
	MAPPARTICLEIT it = m_mapParticle.find( parname );
	if( it != m_mapParticle.end() )
	{
		m_itCurrent = it;

		return (*it).second;
	}
	else 
		return NULL;
}

CParticleItem* CParticleGroup::GetReplaceItemKey( const char* parname, const char* replacename )
{
	MAPPARTICLEIT it = m_mapParticle.find( parname );
	if( it != m_mapParticle.end() )
	{
		CParticleItem* pItem = (*it).second;

		m_mapParticle.erase( it );

		m_itCurrent = m_mapParticle.begin();

		pItem->SetName( replacename );
		m_mapParticle.insert( std::make_pair( replacename, pItem ) );

		return pItem;
	}
	else 
		return NULL;
}

BOOL CParticleGroup::DelParticle( const char* parname )
{
	MAPPARTICLEIT it = m_mapParticle.find( parname );
	if( it != m_mapParticle.end() )
	{
		if( m_itCurrent == it )
			m_itCurrent = m_mapParticle.begin();

		NTL_DELETE( (*it).second );

		m_mapParticle.erase( it );
	
		return TRUE;
	}
	else 
		return FALSE;
}

CParticleItem* CParticleGroup::GetFirstParticle()
{
	MAPPARTICLEIT it = m_mapParticle.begin();
	if( it != m_mapParticle.end() )
	{
		m_itCurrent = it;

		return (*it).second;
	}
	else
		return NULL;
}

CParticleItem* CParticleGroup::GetNextParticle()
{
	m_itCurrent++;
	if( m_itCurrent != m_mapParticle.end() )
		return (*m_itCurrent).second;
	else
		return NULL;
}

CParticleItem* CParticleGroup::GetCurrentParticle()
{
	if( m_itCurrent != m_mapParticle.end() )
		return (*m_itCurrent).second;
	else
		return NULL;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CParticleDoc

// defines..
#define LINE_BUFFER_SIZE 4096
#define TAG_BUFFER_SIZE 32
#define NAME_BUFFER_SIZE 32

#define SCRIPT_LEFT_SIDE_LEGNTH	16
#define SCRIPT_TAB_SIZE	4

CParticleDoc::CParticleDoc()
{
	m_pCurrentGroup = NULL;
	m_pCurrentItem = NULL;
	m_byCurrentValueType = 0xFF;
	m_itCurrent = m_mapGroup.end();

	RegisterHandler();
}

CParticleDoc::~CParticleDoc()
{
	m_pCurrentGroup = NULL;
	m_pCurrentItem = NULL;
	m_byCurrentValueType = 0xFF;

	MAPGROUPIT it = m_mapGroup.begin();
	while( it != m_mapGroup.end() )
	{
		NTL_DELETE( (*it).second );

		++it;
	}
	m_mapGroup.clear();
}

void CParticleDoc::RegisterHandler()
{
	m_hmapHandler["[group"] = &CParticleDoc::ParseGroupHandler;
	m_hmapHandler["[particle"] = &CParticleDoc::ParseParticleHandler;
	m_hmapHandler["[emitter"] = &CParticleDoc::ParseEmitterHandler;
	m_hmapHandler["[affector"] = &CParticleDoc::ParseAffectorHandler;
	m_hmapHandler["[path"] = &CParticleDoc::ParsePathHandler;
}

void CParticleDoc::Load( const char* filename )
{
	if( g_fnCallPack )
	{
		LoadFromPack( filename );
		return;
	}

	FILE* fp;
	fopen_s( &fp, filename, "rt" );
	if( fp == NULL )
	{
		// 파일이 없음
		return;
	}

	// 기존의 자료가 있따면 모두 다 삭제해준다.
	m_pCurrentGroup = NULL;
	m_pCurrentItem = NULL;
	m_byCurrentValueType = 0xFF;

	MAPGROUPIT it = m_mapGroup.begin();
	while( it != m_mapGroup.end() )
	{
		NTL_DELETE( (*it).second );

		++it;
	}
	m_mapGroup.clear();


	char acLineBuffer[LINE_BUFFER_SIZE];
	char acLeftside[LINE_BUFFER_SIZE/2];
	char acRightSide[LINE_BUFFER_SIZE/2];

	// 파일을 한 줄 씩 끊어서 읽는다.
	int nCount = 0;
	while( !feof(fp) )
	{
		fgets( acLineBuffer, sizeof(acLineBuffer), fp );

		// 최소 라인길이가 2 이상이어야지 파싱한다.
		if( strlen(acLineBuffer) >= 2 )
		{
			// 주석으로 처리한다.
			if( acLineBuffer[0] == '/' && acLineBuffer[1] == '/' )
				continue;
			
			char acTagBuffer[TAG_BUFFER_SIZE] = "";
			if( acLineBuffer[0] == '[' )
			{
				ExtractTokenByLastChar( acLineBuffer, acTagBuffer, sizeof( acTagBuffer ), " " );
			}

			// 만약 핸들러에 등록된 태그를 발견했을 경우 새로운 자료구조를 추가한다.
			HMapHandler::iterator it;
			it = m_hmapHandler.find( acTagBuffer );
			if( it != m_hmapHandler.end() )
			{
				// 태그에 따른 핸들러 호출
				(this->*((*it).second))( acLineBuffer );

				continue;
			}

			// 이 두개의 변수가 초기값에서 변경되지 않았다면 순서가 잘못됐거나 스크립트가 잘못되어 있다는 것을 의미함
			if( m_pCurrentItem == NULL || m_byCurrentValueType == CParticleItem::INVALID_ITEM  )
			{
				// Error : 문법 에러~
				assert( 0 && "CParticleDoc::Load - Particle script syntex invalid!" );
				return;
			}

			ExtractTokenByLastChar( acLineBuffer, acLeftside, sizeof(acLeftside), "=" );
			RemoveSpaceForSelfBuffer( acLeftside );
			ExtractTokenByLastChar( acLineBuffer, acRightSide, sizeof(acRightSide), "\n" );
			RemoveSpaceForSelfBuffer( acRightSide );

			m_pCurrentItem->AddValue( (CParticleItem::eItemType)m_byCurrentValueType, acLeftside, acRightSide );
		}

		nCount++;
	}

	fclose( fp );
}

/**
* \brief 팩 모드 일 경우만 사용하는 함수
*/
void CParticleDoc::LoadFromPack( const char* filename )
{
	char* pData = NULL;
	int nTotalSize = 0;
	
	(*g_fnCallPack)(filename, (void**)&pData, (unsigned int*)&nTotalSize);
	if( nTotalSize == 0 )
	{
		DBO_FAIL("2d Particle scripe file load faield - " << filename );
		return;
	}
	
	// 기존의 자료가 있따면 모두 다 삭제해준다.
	m_pCurrentGroup = NULL;
	m_pCurrentItem = NULL;
	m_byCurrentValueType = 0xFF;

	MAPGROUPIT it = m_mapGroup.begin();
	while( it != m_mapGroup.end() )
	{
		NTL_DELETE( (*it).second );

		++it;
	}
	m_mapGroup.clear();


	char acLineBuffer[LINE_BUFFER_SIZE];
	char acLeftside[LINE_BUFFER_SIZE/2];
	char acRightSide[LINE_BUFFER_SIZE/2];

	// 데이타를 하나씩 읽어들인다.
	int nCurPos = -1;
	int nLineStartPos = 0;
	int nLineEndPos = 0;

	while( nCurPos < nTotalSize )
	{
		nCurPos++;

		// 줄넘김 문자가 있는지 확인한다.
		if( pData[nCurPos] == '\n' )
		{
			int nOffset = nCurPos - nLineStartPos;
			memcpy( acLineBuffer, &pData[nLineStartPos], sizeof(char) * (nOffset) );

			nLineStartPos = ++nCurPos;

			if( nCurPos > nTotalSize )
				return;

			acLineBuffer[nOffset] = NULL;

			// 최소 라인길이가 2 이상이어야지 파싱한다.
			if( strlen(acLineBuffer) >= 2 )
			{
				// 주석으로 처리한다.
				if( acLineBuffer[0] == '/' && acLineBuffer[1] == '/' )
					continue;

				char acTagBuffer[TAG_BUFFER_SIZE] = "";
				if( acLineBuffer[0] == '[' )
				{
					ExtractTokenByLastChar( acLineBuffer, acTagBuffer, sizeof( acTagBuffer ), " " );
				}

				// 만약 핸들러에 등록된 태그를 발견했을 경우 새로운 자료구조를 추가한다.
				HMapHandler::iterator it;
				it = m_hmapHandler.find( acTagBuffer );
				if( it != m_hmapHandler.end() )
				{
					// 태그에 따른 핸들러 호출
					(this->*((*it).second))( acLineBuffer );

					continue;
				}

				// 이 두개의 변수가 초기값에서 변경되지 않았다면 순서가 잘못됐거나 스크립트가 잘못되어 있다는 것을 의미함
				if( m_pCurrentItem == NULL || m_byCurrentValueType == CParticleItem::INVALID_ITEM  )
				{
					// Error : 문법 에러~
					assert( 0 && "CParticleDoc::Load - Particle script syntex invalid!" );
					return;
				}

				ExtractTokenByLastChar( acLineBuffer, acLeftside, sizeof(acLeftside), "=" );
				RemoveSpaceForSelfBuffer( acLeftside );
				ExtractTokenByLastChar( acLineBuffer, acRightSide, sizeof(acRightSide), "\n" );
				RemoveSpaceForSelfBuffer( acRightSide );

				m_pCurrentItem->AddValue( (CParticleItem::eItemType)m_byCurrentValueType, acLeftside, acRightSide );
			}
		}
	}

	NTL_ARRAY_DELETE( pData );
}

void CParticleDoc::Save( const char* filename )
{
	FILE* fp;
	fopen_s( &fp, filename, "wt" );
	if( fp == NULL )
	{
		// 오류가 생김
		return;
	}
	
	// 파티클 속성에 대한 정보를 남긴다.
	fprintf_s( fp, "// %s\n", filename );
	fprintf_s( fp, "// Particle Group Count : %d\n", (int)m_mapGroup.size() );
	
	// 파티클 그룹을 읽어온다.
	int nGroupCount = 1;
	gui::CParticleGroup* pGroup = GetFirstGroup();
	while( pGroup )
	{
		// 그룹 이름
		fprintf_s( fp, "\n" );
		fprintf_s( fp, "// Group %d : particle count : %d\n", nGroupCount, pGroup->GetSize() );
		fprintf_s( fp, "[group %s]\n", pGroup->GetName().c_str() );

		// 파티클 그룹에 있는 파티클들을 순회하며 각종 속성들을 읽어온다. :: 동작하는지 확인 해야함
		gui::CParticleItem* pItem = pGroup->GetFirstParticle();
		while( pItem )
		{
			// 공통 속성
			for( int i = CParticleItem::ITEM_COMMON; i < CParticleItem::ITEM_NUMS; ++i )
			{
				gui::CValueItem* pValueItem = pItem->GetValueItem( (CParticleItem::eItemType)i );
				if( pValueItem->GetSize() > 0 )
				{
					switch( (CParticleItem::eItemType)i )
					{
					case CParticleItem::ITEM_COMMON:
						fprintf_s( fp, "[particle %s]\n", pItem->GetName().c_str() );
						break;
					case CParticleItem::ITEM_EMITTER:
						fprintf_s( fp, "[emitter %s]\n", pValueItem->GetName().c_str() );
						break;
					case CParticleItem::ITEM_GRAVITY:
						fprintf_s( fp, "[affector gravity]\n");
						break;
					case CParticleItem::ITEM_COLOR:
						fprintf_s( fp, "[affector color]\n");
						break;
					case CParticleItem::ITEM_PATH:
						fprintf_s( fp, "[path name]\n");
						break;
					default:
						{
							assert( 0 && "Invalid Item Type!!" );
						}
						return;
					}

					// 맵의 속성을 읽어들여서 순회한다.
					gui::CValueItem::VALUEMAP::iterator it = pValueItem->m_mapValue.begin();
					while( it != pValueItem->m_mapValue.end() )
					{
						fprintf_s( fp, "%s = %s\n", ((*it).first).c_str(), ((*it).second).c_str() );

						it++;
					}
				}
			}
			pItem = pGroup->GetNextParticle();
		}
		pGroup = GetNextGroup();
		nGroupCount++;
	}

	fclose( fp );
}

void CParticleDoc::Clear()
{
	m_pCurrentGroup = NULL;
	m_pCurrentItem = NULL;
	m_byCurrentValueType = 0xFF;

	MAPGROUPIT it = m_mapGroup.begin();
	while( it != m_mapGroup.end() )
	{
		NTL_DELETE( (*it).second );
		++it;
	}
	m_mapGroup.clear();
	m_itCurrent = m_mapGroup.begin();
}

CParticleGroup* CParticleDoc::AddParticleGroup( const char* groupname )
{
	// 같은 이름의 파티클 그룹이 없을 경우에만 추가한다.
	MAPGROUPIT it = m_mapGroup.find( groupname );
	if( it == m_mapGroup.end() )
	{
		CParticleGroup* pGroup = NTL_NEW CParticleGroup;
		pGroup->SetName( groupname );
		m_mapGroup.insert( std::make_pair( groupname, pGroup ) );

		return pGroup;
	}

	return NULL;
}

CParticleItem* CParticleDoc::AddParticle( const char* groupname, const char* parname )
{
	// 같은 이름의 파티클 그룹이 있고 그 그룹 안에 동일한 이름의 파티클이 없을 경우에만 추가한다.
	MAPGROUPIT it = m_mapGroup.find( groupname );
	if( it != m_mapGroup.end() )
	{
		return ((*it).second)->AddParticle( parname );
	}

	return NULL;
}

BOOL CParticleDoc::DelParticleGroup( const char* groupname )
{
	MAPGROUPIT it = m_mapGroup.find( groupname );
	if( it != m_mapGroup.end() )
	{
		if( m_itCurrent == it )
			m_itCurrent =m_mapGroup.begin();

		NTL_DELETE( (*it).second );

		m_mapGroup.erase( it );

		return TRUE;
	}
	else 
		return FALSE;
}

BOOL CParticleDoc::DelParticle( const char* groupname, const char* parname )
{
	MAPGROUPIT it = m_mapGroup.find( groupname );
	if( it != m_mapGroup.end() )
	{
		return ((*it).second)->DelParticle( parname );
	}
	
	return FALSE;
}

CParticleGroup* CParticleDoc::GetParticleGroup( const char* pGroupName )
{
	MAPGROUPIT it = m_mapGroup.find( pGroupName );
	if( it != m_mapGroup.end() )
	{
		return (*it).second;
	}
	else
		return NULL;
}

CParticleGroup* CParticleDoc::GetReplaceGroupKey( const char* pGroupName, const char* pReplaceName )
{
	MAPGROUPIT it = m_mapGroup.find( pGroupName );
	if( it != m_mapGroup.end() )
	{
		gui::CParticleGroup* pGroup = (*it).second;

		m_mapGroup.erase( it );

		pGroup->SetName( pReplaceName );
		m_mapGroup.insert( std::make_pair( pReplaceName, pGroup ) );

		return pGroup;
	}
	else
		return NULL;
}

CParticleGroup* CParticleDoc::GetFirstGroup()
{
	m_itCurrent = m_mapGroup.begin();
	if( m_itCurrent != m_mapGroup.end() )
	{
		return (*m_itCurrent).second;
	}
	else
		return NULL;
}

CParticleGroup* CParticleDoc::GetNextGroup()
{
	m_itCurrent++;
	if( m_itCurrent != m_mapGroup.end() )
		return (*m_itCurrent).second;
	else
		return NULL;
}

CParticleGroup* CParticleDoc::GetCurrentGroup()
{
	if( m_itCurrent != m_mapGroup.end() )
		return (*m_itCurrent).second;
	else
		return NULL;
}

BOOL CParticleDoc::ParseGroupHandler( char* pLineBuffer )
{
	char* pEndPos = strstr( pLineBuffer, "]" );
	if( pEndPos == NULL )
	{
		// Error : 닫혀 있지 않다.
		return FALSE;
	}

	int nNameSize = (int)( pEndPos - pLineBuffer );
	
	char acBuffer[NAME_BUFFER_SIZE] = "";
	memcpy( acBuffer, pLineBuffer, nNameSize );
	RemoveSpaceForSelfBuffer( acBuffer );

	// 1. 새로운 그룹을 생성
	// 2. m_pCurrentGroup = 새로운 그룹의 포인터
	// 3. 새로운 그룹의 이름을 정한다.
	// 4. 그룹 맵에 추가!!!!
	CParticleGroup* pGroup = NTL_NEW CParticleGroup;
	m_pCurrentGroup = pGroup;
	pGroup->SetName( acBuffer );
	m_mapGroup.insert( std::make_pair( acBuffer, pGroup ) );

	return TRUE;
}

BOOL CParticleDoc::ParseParticleHandler( char* pLineBuffer )
{
	char* pEndPos = strstr( pLineBuffer, "]" );
	if( pEndPos == NULL )
	{
		// Error : 닫혀 있지 않다.
		return FALSE;
	}

	int nNameSize = (int)( pEndPos - pLineBuffer );

	char acBuffer[NAME_BUFFER_SIZE] = "";
	memcpy( acBuffer, pLineBuffer, nNameSize );
	RemoveSpaceForSelfBuffer( acBuffer );

	// 그룹의 포인터가 NULL 이라면 그룹이 생성된 적이 없다는 것
	if( m_pCurrentGroup == NULL )
	{
		// Error : 현재 있는 파티클 태그가 위치가 맞지 않다.
		return FALSE;
	}

	// 파티클 아이템을 생성해서 현재 있는 그룹에 추가한다.
	CParticleItem* pItem = m_pCurrentGroup->AddParticle( acBuffer );
	if( pItem == NULL )
	{
		// 파티클 아이템의 중복 

		return FALSE;
	}
	
	m_pCurrentItem = pItem;
	m_byCurrentValueType = CParticleItem::ITEM_COMMON;

	return TRUE;
}

BOOL CParticleDoc::ParseEmitterHandler( char* pLineBuffer )
{
	char* pEndPos = strstr( pLineBuffer, "]" );
	if( pEndPos == NULL )
	{
		// Error : 닫혀 있지 않다.
		return FALSE;
	}

	int nNameSize = (int)( pEndPos - pLineBuffer );

	char acBuffer[NAME_BUFFER_SIZE] = "";
	memcpy( acBuffer, pLineBuffer, nNameSize );
	RemoveSpaceForSelfBuffer( acBuffer );

	// 문법 에러 체크
	if( m_pCurrentGroup == NULL || m_pCurrentItem == NULL )
	{
		// Error : 현재 있는 이미터 태그의 위치가 알맞지 않다.
		return FALSE;
	}

	m_byCurrentValueType = CParticleItem::ITEM_EMITTER;
	m_pCurrentItem->SetValueItemName( (CParticleItem::eItemType)m_byCurrentValueType, acBuffer );
	m_pCurrentItem->SetValueItemType( (CParticleItem::eItemType)m_byCurrentValueType, "emitter" );

	return TRUE;
}

BOOL CParticleDoc::ParseAffectorHandler( char* pLineBuffer )
{
	char* pEndPos = strstr( pLineBuffer, "]" );
	if( pEndPos == NULL )
	{
		// Error : 닫혀 있지 않다.
		return FALSE;
	}

	int nNameSize = (int)( pEndPos - pLineBuffer );

	char acBuffer[NAME_BUFFER_SIZE] = "";
	memcpy( acBuffer, pLineBuffer, nNameSize );
	RemoveSpaceForSelfBuffer( acBuffer );

	// 문법 에러 체크
	if( m_pCurrentGroup == NULL || m_pCurrentItem == NULL )
	{
		// Error : 현재 있는 이미터 태그의 위치가 알맞지 않다.
		return FALSE;
	}

	if( strcmp( acBuffer , "gravity" ) == 0 )
	{
		m_byCurrentValueType = CParticleItem::ITEM_GRAVITY;
		m_pCurrentItem->SetValueItemName( (CParticleItem::eItemType)m_byCurrentValueType, acBuffer );
		m_pCurrentItem->SetValueItemType( (CParticleItem::eItemType)m_byCurrentValueType, "gravity" );
	}
	else if( strcmp( acBuffer, "color" ) == 0 )
	{
		m_byCurrentValueType = CParticleItem::ITEM_COLOR;
		m_pCurrentItem->SetValueItemName( (CParticleItem::eItemType)m_byCurrentValueType, acBuffer );
		m_pCurrentItem->SetValueItemType( (CParticleItem::eItemType)m_byCurrentValueType, "color" );
	}

	return TRUE;
}

BOOL CParticleDoc::ParsePathHandler( char* pLineBuffer )
{
	char* pEndPos = strstr( pLineBuffer, "]" );
	if( pEndPos == NULL )
	{
		// Error : 닫혀 있지 않다.
		return FALSE;
	}

	int nNameSize = (int)( pEndPos - pLineBuffer );

	char acBuffer[NAME_BUFFER_SIZE] = "";
	memcpy( acBuffer, pLineBuffer, nNameSize );
	RemoveSpaceForSelfBuffer( acBuffer );

	// 문법 에러 체크
	if( m_pCurrentGroup == NULL || m_pCurrentItem == NULL )
	{
		// Error : 현재 있는 이미터 태그의 위치가 알맞지 않다.
		return FALSE;
	}

	m_byCurrentValueType = CParticleItem::ITEM_PATH;
	/*m_pCurrentItem->SetValueItemName( (CParticleItem::eItemType)m_byCurrentValueType, acBuffer );*/

	return TRUE;
}


END_GUI


