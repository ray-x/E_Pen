// Config.cpp : implementation file
//

#include "stdafx.h"
#include "TipTopPenBeta.h"
#include "Config.h"


// CConfig dialog

IMPLEMENT_DYNAMIC(CConfig, CDialog)

CConfig::CConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CConfig::IDD, pParent)
{

}

CConfig::~CConfig()
{
}

void CConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfig, CDialog)
END_MESSAGE_MAP()


// CConfig message handlers
