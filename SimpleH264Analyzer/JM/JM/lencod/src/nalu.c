/**********************************************************************
 * Software Copyright Licensing Disclaimer
 *
 * This software module was originally developed by contributors to the
 * course of the development of ISO/IEC 14496-10 for reference purposes
 * and its performance may not have been optimized.  This software
 * module is an implementation of one or more tools as specified by
 * ISO/IEC 14496-10.  ISO/IEC gives users free license to this software
 * module or modifications thereof. Those intending to use this software
 * module in products are advised that its use may infringe existing
 * patents.  ISO/IEC have no liability for use of this software module
 * or modifications thereof.  The original contributors retain full
 * rights to modify and use the code for their own purposes, and to
 * assign or donate the code to third-parties.
 *
 * This copyright notice must be included in all copies or derivative
 * works.  Copyright (c) ISO/IEC 2004.
 **********************************************************************/

/*!
 ************************************************************************
 * \file  nalu.c
 *
 * \brief
 *    Common NALU support functions
 *
 * \author
 *    Main contributors (see contributors.h for copyright, address and affiliation details)
 *    - Stephan Wenger   <stewe@cs.tu-berlin.de>
 ************************************************************************
 */

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "memory.h"

#include "global.h"
#include "nalu.h"

/*! 
 *************************************************************************************
 * \brief
 *    Converts an RBSP to a NALU
 *
 * \param rbsp
 *    byte buffer with the rbsp
 * \param nalu
 *    nalu structure to be filled
 * \param rbsp_size
 *    size of the rbsp in bytes
 * \param nal_unit_type
 *    as in JVT doc
 * \param nal_reference_idc
 *    as in JVT doc
 * \param min_num_bytes
 *    some incomprehensible CABAC stuff
 * \param UseAnnexbLongStartcode
 *    when 1 and when using AnnexB bytestreams, then use a long startcode prefix
 *
 * \return
 *    length of the NALU in bytes
 *************************************************************************************
 */

int RBSPtoNALU (char *rbsp, NALU_t *nalu, int rbsp_size, int nal_unit_type, int nal_reference_idc, 
                int min_num_bytes, int UseAnnexbLongStartcode)
{
  int len;

  assert (nalu != NULL);
  assert (nal_reference_idc <=3 && nal_reference_idc >=0);
  assert (nal_unit_type > 0 && nal_unit_type <= 10);
  assert (rbsp_size < MAXRBSPSIZE);

  nalu->forbidden_bit = 0;
  nalu->nal_reference_idc = nal_reference_idc;
  nalu->nal_unit_type = nal_unit_type;
  nalu->startcodeprefix_len = UseAnnexbLongStartcode?4:3;
  nalu->buf[0] =
    nalu->forbidden_bit << 7      |
    nalu->nal_reference_idc << 5  |
    nalu->nal_unit_type;

  memcpy (&nalu->buf[1], rbsp, rbsp_size);
// printf ("First Byte %x\n", nalu->buf[0]);
// printf ("RBSPtoNALU: Before: NALU len %d\t RBSP %x %x %x %x\n", rbsp_size, (unsigned) nalu->buf[1], (unsigned) nalu->buf[2], (unsigned) nalu->buf[3], (unsigned) nalu->buf[4]);

  len = 1 + RBSPtoEBSP (&nalu->buf[1], 0, rbsp_size, min_num_bytes);

// printf ("RBSPtoNALU: After : NALU len %d\t EBSP %x %x %x %x\n", rbsp_size, (unsigned) nalu->buf[1], (unsigned) nalu->buf[2], (unsigned) nalu->buf[3], (unsigned) nalu->buf[4]);
// printf ("len %d\n\n", len);
  nalu->len = len;

  return len;
}


