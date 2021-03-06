#include "precomp_trigger.h"
#include "DboTSCheckAttachObj.h"


/**
	Check attach object
*/


NTL_TS_IMPLEMENT_RTTI( CDboTSCheckAttachObj, CNtlTSCond )


CDboTSCheckAttachObj::CDboTSCheckAttachObj( void )
: m_uiWorldIdx( 0xffffffff )
{
}

void CDboTSCheckAttachObj::SetWorldIdx( unsigned int uiWorldIdx )
{
	m_uiWorldIdx = uiWorldIdx;
}

bool CDboTSCheckAttachObj::HasObjectIdx( unsigned int uiObjIdx )
{
	mapdef_OBJECT_LIST::iterator it = m_defObjIdxList.find( uiObjIdx );
	if ( it == m_defObjIdxList.end() ) return false;
	return true;
}

unsigned int CDboTSCheckAttachObj::BeginObjectIdx( void )
{
	m_defObjIdxListIT = m_defObjIdxList.begin();
	if ( m_defObjIdxListIT == m_defObjIdxList.end() ) return 0xffffffff;
	return m_defObjIdxListIT->second;
}

unsigned int CDboTSCheckAttachObj::NextObjectIdx( void )
{
	if ( m_defObjIdxListIT == m_defObjIdxList.end() ) return 0xffffffff;
	m_defObjIdxListIT++;
	if ( m_defObjIdxListIT == m_defObjIdxList.end() ) return 0xffffffff;
	return m_defObjIdxListIT->second;
}

void CDboTSCheckAttachObj::ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty )
{
	CNtlTSCond::ApplyScriptDataForScript( clProperty );

	if ( clProperty.IsExist( "widx" ) )
	{
		SetWorldIdx( clProperty.GetValueAsInt( "widx" ) );
	}

	if ( clProperty.IsExist( "objidx" ) )
	{
		UnPackingObjectIdxList( clProperty.GetValue( "objidx" ), m_defObjIdxList );
	}
}

void CDboTSCheckAttachObj::TakeScriptDataForScript( CNtlTSScrProperty& clProperty )
{
	CNtlTSCond::TakeScriptDataForScript( clProperty );

	sprintf_s( g_NtlTSString, "%d", GetWorldIdx() );
	clProperty.m_defProperty["widx"] = g_NtlTSString;

	std::string strObjList;
	PackingObjectIdxList( strObjList, m_defObjIdxList );
	if ( !strObjList.empty() )
	{
		clProperty.m_defProperty["objidx"] = strObjList;
	}
}

void CDboTSCheckAttachObj::PackingObjectIdxList( std::string& strObjList, const CDboTSCheckAttachObj::mapdef_OBJECT_LIST& defObjList )
{
	strObjList.clear();

	mapdef_OBJECT_LIST::const_iterator cit = defObjList.begin();
	for ( ; cit != defObjList.end(); ++cit )
	{
		sprintf_s( g_NtlTSString, "%d;", cit->first );
		strObjList += g_NtlTSString;
	}
}

void CDboTSCheckAttachObj::UnPackingObjectIdxList( const std::string& strObjList, CDboTSCheckAttachObj::mapdef_OBJECT_LIST& defObjList )
{
	defObjList.clear();

	std::string strObjIdx;
	strObjIdx.reserve( 10 );

	std::string::const_iterator cit = strObjList.begin();
	for ( ; cit != strObjList.end(); ++cit )
	{
		if ( ';' == *cit )
		{
			unsigned int uiObjIdx = atoi( strObjIdx.c_str() );
			strObjIdx.clear();

			defObjList[uiObjIdx] = uiObjIdx;
		}
		else if ( '0' > *cit || '9' < *cit )
		{
			defObjList.clear();
			CNtlTSLog::Log( "Only must have numbers. Info[%s]. [%s]", strObjList.c_str(), TS_CODE_TRACE() );
			return;
		}
		else
		{
			strObjIdx += *cit;
		}
	}

	if ( !strObjIdx.empty() )
	{
		unsigned int uiObjIdx = atoi( strObjIdx.c_str() );
		strObjIdx.clear();

		defObjList[uiObjIdx] = uiObjIdx;
	}
}
