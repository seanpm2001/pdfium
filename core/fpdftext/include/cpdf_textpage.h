// Copyright 2016 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FPDFTEXT_INCLUDE_CPDF_TEXTPAGE_H_
#define CORE_FPDFTEXT_INCLUDE_CPDF_TEXTPAGE_H_

#include <deque>
#include <vector>

#include "core/fpdfapi/fpdf_page/cpdf_pageobjectlist.h"
#include "core/fxcrt/include/fx_basic.h"
#include "core/fxcrt/include/fx_coordinates.h"
#include "core/fxcrt/include/fx_string.h"

class CFX_BidiChar;
class CPDF_Font;
class CPDF_FormObject;
class CPDF_Page;
class CPDF_TextObject;

struct FPDF_CHAR_INFO {
  FX_WCHAR m_Unicode;
  FX_WCHAR m_Charcode;
  int32_t m_Flag;
  FX_FLOAT m_FontSize;
  FX_FLOAT m_OriginX;
  FX_FLOAT m_OriginY;
  CFX_FloatRect m_CharBox;
  CPDF_TextObject* m_pTextObj;
  CFX_Matrix m_Matrix;
};

struct FPDF_SEGMENT {
  int m_Start;
  int m_nCount;
};

struct PAGECHAR_INFO {
  int m_CharCode;
  FX_WCHAR m_Unicode;
  FX_FLOAT m_OriginX;
  FX_FLOAT m_OriginY;
  int32_t m_Flag;
  CFX_FloatRect m_CharBox;
  CPDF_TextObject* m_pTextObj;
  CFX_Matrix m_Matrix;
  int m_Index;
};

struct PDFTEXT_Obj {
  CPDF_TextObject* m_pTextObj;
  CFX_Matrix m_formMatrix;
};

class CPDF_TextPage {
 public:
  CPDF_TextPage(const CPDF_Page* pPage, int flags);
  ~CPDF_TextPage() {}

  // IPDF_TextPage:
  void ParseTextPage();
  bool IsParsed() const { return m_bIsParsed; }
  int CharIndexFromTextIndex(int TextIndex) const;
  int TextIndexFromCharIndex(int CharIndex) const;
  int CountChars() const;
  void GetCharInfo(int index, FPDF_CHAR_INFO* info) const;
  void GetRectArray(int start, int nCount, CFX_RectArray& rectArray) const;
  int GetIndexAtPos(CFX_FloatPoint point,
                    FX_FLOAT xTolerance,
                    FX_FLOAT yTolerance) const;
  int GetIndexAtPos(FX_FLOAT x,
                    FX_FLOAT y,
                    FX_FLOAT xTolerance,
                    FX_FLOAT yTolerance) const;
  CFX_WideString GetTextByRect(const CFX_FloatRect& rect) const;
  void GetRectsArrayByRect(const CFX_FloatRect& rect,
                           CFX_RectArray& resRectArray) const;
  CFX_WideString GetPageText(int start = 0, int nCount = -1) const;
  int CountRects(int start, int nCount);
  void GetRect(int rectIndex,
               FX_FLOAT& left,
               FX_FLOAT& top,
               FX_FLOAT& right,
               FX_FLOAT& bottom) const;
  FX_BOOL GetBaselineRotate(int rectIndex, int& Rotate);
  FX_BOOL GetBaselineRotate(const CFX_FloatRect& rect, int& Rotate);
  int CountBoundedSegments(FX_FLOAT left,
                           FX_FLOAT top,
                           FX_FLOAT right,
                           FX_FLOAT bottom,
                           FX_BOOL bContains = FALSE);
  void GetBoundedSegment(int index, int& start, int& count) const;
  int GetWordBreak(int index, int direction) const;

  static FX_BOOL IsRectIntersect(const CFX_FloatRect& rect1,
                                 const CFX_FloatRect& rect2);
  static FX_BOOL IsLetter(FX_WCHAR unicode);

 private:
  FX_BOOL IsHyphen(FX_WCHAR curChar);
  bool IsControlChar(const PAGECHAR_INFO& charInfo);
  FX_BOOL GetBaselineRotate(int start, int end, int& Rotate);
  void ProcessObject();
  void ProcessFormObject(CPDF_FormObject* pFormObj,
                         const CFX_Matrix& formMatrix);
  void ProcessTextObject(PDFTEXT_Obj pObj);
  void ProcessTextObject(CPDF_TextObject* pTextObj,
                         const CFX_Matrix& formMatrix,
                         const CPDF_PageObjectList* pObjList,
                         CPDF_PageObjectList::const_iterator ObjPos);
  int ProcessInsertObject(const CPDF_TextObject* pObj,
                          const CFX_Matrix& formMatrix);
  FX_BOOL GenerateCharInfo(FX_WCHAR unicode, PAGECHAR_INFO& info);
  FX_BOOL IsSameAsPreTextObject(CPDF_TextObject* pTextObj,
                                const CPDF_PageObjectList* pObjList,
                                CPDF_PageObjectList::const_iterator ObjPos);
  FX_BOOL IsSameTextObject(CPDF_TextObject* pTextObj1,
                           CPDF_TextObject* pTextObj2);
  int GetCharWidth(uint32_t charCode, CPDF_Font* pFont) const;
  void CloseTempLine();
  void OnPiece(CFX_BidiChar* pBidi, CFX_WideString& str);
  int32_t PreMarkedContent(PDFTEXT_Obj pObj);
  void ProcessMarkedContent(PDFTEXT_Obj pObj);
  void CheckMarkedContentObject(int32_t& start, int32_t& nCount) const;
  void FindPreviousTextObject(void);
  void AddCharInfoByLRDirection(FX_WCHAR wChar, PAGECHAR_INFO info);
  void AddCharInfoByRLDirection(FX_WCHAR wChar, PAGECHAR_INFO info);
  int32_t GetTextObjectWritingMode(const CPDF_TextObject* pTextObj);
  int32_t FindTextlineFlowDirection();

  void SwapTempTextBuf(int32_t iCharListStartAppend, int32_t iBufStartAppend);
  FX_BOOL IsRightToLeft(const CPDF_TextObject* pTextObj,
                        const CPDF_Font* pFont,
                        int nItems) const;

  const CPDF_Page* const m_pPage;
  std::vector<uint16_t> m_CharIndex;
  std::deque<PAGECHAR_INFO> m_CharList;
  std::deque<PAGECHAR_INFO> m_TempCharList;
  CFX_WideTextBuf m_TextBuf;
  CFX_WideTextBuf m_TempTextBuf;
  const int m_parserflag;
  CPDF_TextObject* m_pPreTextObj;
  CFX_Matrix m_perMatrix;
  bool m_bIsParsed;
  CFX_Matrix m_DisplayMatrix;
  CFX_ArrayTemplate<FPDF_SEGMENT> m_Segments;
  CFX_RectArray m_SelRects;
  CFX_ArrayTemplate<PDFTEXT_Obj> m_LineObj;
  int32_t m_TextlineDir;
  CFX_FloatRect m_CurlineRect;
};

#endif  // CORE_FPDFTEXT_INCLUDE_CPDF_TEXTPAGE_H_
