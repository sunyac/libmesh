// $Id$

// The libMesh Finite Element Library.
// Copyright (C) 2002-2007  Benjamin S. Kirk, John W. Peterson
  
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
  
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
  
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



#ifndef __xdr_io_io_h__
#define __xdr_io_io_h__


// C++ inludes

// Local includes
#include "mesh_input.h"
#include "mesh_output.h"

// Forward declarations
class MeshBase;
class MeshData;

/**
 *
 * @author Benjamin Kirk, John Peterson, 2004.
 */

// ------------------------------------------------------------
// XdrIO class definition
class XdrIO : public MeshInput<MeshBase>,
	      public MeshOutput<MeshBase>
{

 public:
   /**
    * Enumeration flag for the type of software.
    * DEAL is old-style LibMesh files without adaptivity
    * MGF  is for files created by the MGF software package
    * LIBM is for new files generated by LibMesh with adaptivity.
    *      You will likely use this one most often.
    */
   enum FileFormat {DEAL=0, MGF=1, LIBM=2};

  /**
   * Constructor.  Takes a writeable reference to a mesh object.
   * This is the constructor required to read a mesh.
   * The optional parameter \p binary can be used to switch
   * between ASCII (\p false, the default) or binary (\p true)
   * files.
   */
  XdrIO (MeshBase&,       const bool=false);

  /**
   * Constructor.  Takes a reference to a constant mesh object.
   * This constructor will only allow us to write the mesh.
   * The optional parameter \p binary can be used to switch
   * between ASCII (\p false, the default) or binary (\p true)
   * files.
   */
  XdrIO (const MeshBase&, const bool=false);
  
  /**
   * Destructor.
   */
  virtual ~XdrIO ();
  
  /**
   * This method implements reading a mesh from a specified file.
   */
  virtual void read (const std::string&);
  
  /**
   * This method implements reading a mesh in the \p MGF
   * format from a specified file.
   */
  void read_mgf (const std::string&);
  
  /**
   * This method implements writing a mesh to a specified file.
   */
  virtual void write (const std::string&);
  
  /**
   * This method implements writing a mesh in the \p MGF
   * format from a specified file.
   */
  void write_mgf (const std::string&);
    
  /**
   * Read solutions in mgflo's XDR format.
   * Should be compatible with the MGF
   * solution file format. This method expects
   * an ASCII file.  What is MGF?  It was a microgravity
   * fluid physics code developed under a NASA ESS Grand
   * Challenge Grant.  This method exists solely for
   * backwards compatiblity with MGF and could be
   * deprecated at any time.
   */
  void read_mgf_soln (const std::string& name,
		      std::vector<Number>& soln,
		      std::vector<std::string>& var_names) const;
    
  /**
   * Write solutions in mgflo's XDR format.
   * Should be compatible with the MGF
   * solution file format. What is MGF?  It was a microgravity
   * fluid physics code developed under a NASA ESS Grand
   * Challenge Grant.  This method exists solely for
   * backwards compatiblity with MGF and could be
   * deprecated at any time.
   */
  void write_mgf_soln (const std::string& name,
		       std::vector<Number>& soln,
		       std::vector<std::string>& var_names) const;  

  /**
   * Set the flag indicating if we should read/write binary.
   */
  bool & binary();

  /**
   * Read the flag indicating if we should read/write binary.
   */
  bool binary() const;

  
 private:

  /**
   * Read meshes in \p libMesh XDR format.
   * Should be compatible with the mgf
   * mesh file formats.  This method actually
   * expects an ASCII-file.
   */
  void read_ascii (const std::string&, const XdrIO::FileFormat = XdrIO::LIBM);

  /**
   * Read meshes in \p libMesh XDR format.
   * Should be compatible with the mgf
   * mesh file formats.  This method
   * expects an XDR-encoded binary file.
   */
  void read_binary (const std::string&, const XdrIO::FileFormat = XdrIO::LIBM);

  
  
  /**
   * Write meshes in \p libMesh XDR format.
   * Note: MGF won't be able to read these
   * meshes in general since they will be
   * hybrid meshes.  The types are:
   * 0: "DEAL" old type libmesh meshes without refinement 
   * 1: "MGF " even older style meshes from MGF
   * 2: "LIBM" new type meshes which contain refinement trees.
   */
  void write_ascii (const std::string&, const XdrIO::FileFormat = XdrIO::LIBM);

  /**
   * Write meshes in \p libMesh  XDR format.
   * Note: MGF won't be able to read these
   * meshes in general since they will be
   * hybrid meshes.
   */
  void write_binary (const std::string&, const XdrIO::FileFormat = XdrIO::LIBM);


  /**
   * Implements reading either a binary \p XDR or ASCII \p XDA mesh.
   */ 
  void read_mesh (const std::string&,
		  const XdrIO::FileFormat = XdrIO::LIBM,
		  MeshData* = NULL);

  /**
   * Implements writing either a binary \p XDR or ASCII \p XDA mesh.
   */ 
  void write_mesh (const std::string&,
		   const XdrIO::FileFormat = XdrIO::LIBM);

  /**
   * Implements reading either a binary or ASCII MGF solution.
   */
  void read_soln  (const std::string&,
		   std::vector<Real>&,
		   std::vector<std::string>&) const;
  
  /**
   * Implements writing either a binary or ASCII MGF solution.
   */
  void write_soln (const std::string& name,
		   std::vector<Real>& soln,
		   std::vector<std::string>&) const;

  //-------------------------------------------------------------
  // local data

  /**
   * should we read/write binary?
   */
  bool _binary;
};






#endif // #define __xdr_io_h__
