/*=auto=========================================================================

  Portions (c) Copyright 2006 Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Program:   3D Slicer
  Module:    $RCSfile: vtkMRMLProceduralColorNode.h,v $
  Date:      $Date: 2006/03/19 17:12:28 $
  Version:   $Revision: 1.0 $

=========================================================================auto=*/

#ifndef __vtkMRMLProceduralColorNode_h
#define __vtkMRMLProceduralColorNode_h

#include "vtkMRMLColorNode.h"

class vtkColorTransferFunction;

/// \brief MRML node to represent procedurally defined color information.
///
/// Procedural nodes define methods that are used to map colours to scalar
/// values. Usually they will incorporate a custom subclass of a
/// vtkLookupTable, or a vtkColorTransferFunction.
class VTK_MRML_EXPORT vtkMRMLProceduralColorNode : public vtkMRMLColorNode
{
public:
  static vtkMRMLProceduralColorNode *New();
  vtkTypeMacro(vtkMRMLProceduralColorNode,vtkMRMLColorNode);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  //--------------------------------------------------------------------------
  /// MRMLNode methods
  //--------------------------------------------------------------------------

  virtual vtkMRMLNode* CreateNodeInstance();

  /// 
  /// Set node attributes
  virtual void ReadXMLAttributes( const char** atts);

  /// 
  /// Write this node's information to a MRML file in XML format.
  virtual void WriteXML(ostream& of, int indent);
  
  /// 
  /// Copy the node's attributes to this object
  virtual void Copy(vtkMRMLNode *node);
  
  /// 
  /// Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() {return "ProceduralColor";};

  /// 
  /// 
  virtual void UpdateScene(vtkMRMLScene *scene);

  /// 
  /// return a text string describing the colour look up table type
  virtual const char * GetTypeAsString();

  void ProcessMRMLEvents ( vtkObject *caller, unsigned long event, void *callData );

  /// The list of valid procedural types
  //enum
  //{
  ///  
  //};

  /// DisplayModifiedEvent is generated when display node parameters is changed
  enum
    {
      DisplayModifiedEvent = 20000
    };

  /// 
  /// Get the color transfer function for this node
  vtkGetObjectMacro(ColorTransferFunction, vtkColorTransferFunction);

  /// Reimplemented vtkMRMLColorNode::GetScalarsToColors() to return the
  /// transfer function instead of the empty lookuptable
  virtual vtkScalarsToColors* GetScalarsToColors();

  /// 
  /// set up some names, going from the points defined in the transfer function
  bool SetNameFromColor(int index);
  
  virtual int GetNumberOfColors();
  virtual bool GetColor(int entry, double* color);

protected:
  vtkMRMLProceduralColorNode();
  ~vtkMRMLProceduralColorNode();
  vtkMRMLProceduralColorNode(const vtkMRMLProceduralColorNode&);
  void operator=(const vtkMRMLProceduralColorNode&);
  
  /// 
  /// a color transfer function built up by calls to AddRGBPoint and Build
  vtkColorTransferFunction *ColorTransferFunction;
};

#endif
