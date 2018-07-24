// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef FXJS_XFA_CJX_DATETIME_H_
#define FXJS_XFA_CJX_DATETIME_H_

#include "fxjs/jse_define.h"
#include "fxjs/xfa/cjx_node.h"

class CXFA_DateTime;

class CJX_DateTime : public CJX_Node {
 public:
  explicit CJX_DateTime(CXFA_DateTime* node);
  ~CJX_DateTime() override;

  JSE_PROP(defaultValue); /* {default} */
  JSE_PROP(use);
  JSE_PROP(usehref);
  JSE_PROP(value);
};

#endif  // FXJS_XFA_CJX_DATETIME_H_
