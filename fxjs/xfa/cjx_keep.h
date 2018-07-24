// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef FXJS_XFA_CJX_KEEP_H_
#define FXJS_XFA_CJX_KEEP_H_

#include "fxjs/jse_define.h"
#include "fxjs/xfa/cjx_node.h"

class CXFA_Keep;

class CJX_Keep : public CJX_Node {
 public:
  explicit CJX_Keep(CXFA_Keep* node);
  ~CJX_Keep() override;

  JSE_PROP(intact);
  JSE_PROP(next);
  JSE_PROP(previous);
  JSE_PROP(use);
  JSE_PROP(usehref);
};

#endif  // FXJS_XFA_CJX_KEEP_H_
