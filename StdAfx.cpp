// stdafx.cpp : source file that includes just the standard includes
//	GL_Two.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

extern void AFXAPI AfxSetWindowText(HWND hWndCtrl, LPCTSTR lpszNew);

void AFXAPI GLTextFloatFormat(CDataExchange* pDX, int nIDC, void* pData, double value, int nSizeGcvt)
{
   ASSERT(pData != NULL);

   pDX->PrepareEditCtrl(nIDC);
   HWND hWndCtrl;
   pDX->m_pDlgWnd->GetDlgItem(nIDC, &hWndCtrl);

   const int TEXT_BUFFER_SIZE = 64;
   TCHAR szBuffer[TEXT_BUFFER_SIZE] = { 0 };
   if (pDX->m_bSaveAndValidate)
   {
      ::GetWindowText(hWndCtrl, szBuffer, _countof(szBuffer));
      double d;
      if (_sntscanf_s(szBuffer, _countof(szBuffer), _T("%lf"), &d) != 1)
      {
         AfxMessageBox(AFX_IDP_PARSE_REAL);
         pDX->Fail();            // throws exception
      }
      if (nSizeGcvt == FLT_DIG)
         *((float*)pData) = (float)d;
      else
         *((double*)pData) = d;
   }
   else
   {
      ATL_CRT_ERRORCHECK_SPRINTF(_sntprintf_s(szBuffer, _countof(szBuffer), _countof(szBuffer) - 1, _T("%.*g"), nSizeGcvt, value));
      AfxSetWindowText(hWndCtrl, szBuffer);
   }
}

