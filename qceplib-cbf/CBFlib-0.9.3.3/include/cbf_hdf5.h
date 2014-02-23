/**********************************************************************
 * cbf_hdf5.h -- read and write HDF5/NeXus files                      *
 *                                                                    *
 * Version 0.9.3 21 December 2012                                     *
 *                                                                    *
 *                          Paul Ellis and                            *
 *         Herbert J. Bernstein (yaya@bernstein-plus-sons.com)        *
 *                                                                    *
 * (C) Copyright 2009, 2012 Herbert J. Bernstein                      *
 *                                                                    *
 **********************************************************************/

/**********************************************************************
 *                                                                    *
 * YOU MAY REDISTRIBUTE THE CBFLIB PACKAGE UNDER THE TERMS OF THE GPL *
 *                                                                    *
 * ALTERNATIVELY YOU MAY REDISTRIBUTE THE CBFLIB API UNDER THE TERMS  *
 * OF THE LGPL                                                        *
 *                                                                    *
 **********************************************************************/

/*************************** GPL NOTICES ******************************
 *                                                                    *
 * This program is free software; you can redistribute it and/or      *
 * modify it under the terms of the GNU General Public License as     *
 * published by the Free Software Foundation; either version 2 of     *
 * (the License, or (at your option) any later version.               *
 *                                                                    *
 * This program is distributed in the hope that it will be useful,    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      *
 * GNU General Public License for more details.                       *
 *                                                                    *
 * You should have received a copy of the GNU General Public License  *
 * along with this program; if not, write to the Free Software        *
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA           *
 * 02111-1307  USA                                                    *
 *                                                                    *
 **********************************************************************/

/************************* LGPL NOTICES *******************************
 *                                                                    *
 * This library is free software; you can redistribute it and/or      *
 * modify it under the terms of the GNU Lesser General Public         *
 * License as published by the Free Software Foundation; either       *
 * version 2.1 of the License, or (at your option) any later version. *
 *                                                                    *
 * This library is distributed in the hope that it will be useful,    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  *
 * Lesser General Public License for more details.                    *
 *                                                                    *
 * You should have received a copy of the GNU Lesser General Public   *
 * License along with this library; if not, write to the Free         *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,    *
 * MA  02110-1301  USA                                                *
 *                                                                    *
 **********************************************************************/

/**********************************************************************
 *                                                                    *
 *                    Stanford University Notices                     *
 *  for the CBFlib software package that incorporates SLAC software   *
 *                 on which copyright is disclaimed                   *
 *                                                                    *
 * This software                                                      *
 * -------------                                                      *
 * The term ‘this software’, as used in these Notices, refers to      *
 * those portions of the software package CBFlib that were created by *
 * employees of the Stanford Linear Accelerator Center, Stanford      *
 * University.                                                        *
 *                                                                    *
 * Stanford disclaimer of copyright                                   *
 * --------------------------------                                   *
 * Stanford University, owner of the copyright, hereby disclaims its  *
 * copyright and all other rights in this software.  Hence, anyone    *
 * may freely use it for any purpose without restriction.             *
 *                                                                    *
 * Acknowledgement of sponsorship                                     *
 * ------------------------------                                     *
 * This software was produced by the Stanford Linear Accelerator      *
 * Center, Stanford University, under Contract DE-AC03-76SFO0515 with *
 * the Department of Energy.                                          *
 *                                                                    *
 * Government disclaimer of liability                                 *
 * ----------------------------------                                 *
 * Neither the United States nor the United States Department of      *
 * Energy, nor any of their employees, makes any warranty, express or *
 * implied, or assumes any legal liability or responsibility for the  *
 * accuracy, completeness, or usefulness of any data, apparatus,      *
 * product, or process disclosed, or represents that its use would    *
 * not infringe privately owned rights.                               *
 *                                                                    *
 * Stanford disclaimer of liability                                   *
 * --------------------------------                                   *
 * Stanford University makes no representations or warranties,        *
 * express or implied, nor assumes any liability for the use of this  *
 * software.                                                          *
 *                                                                    *
 * Maintenance of notices                                             *
 * ----------------------                                             *
 * In the interest of clarity regarding the origin and status of this *
 * software, this and all the preceding Stanford University notices   *
 * are to remain affixed to any copy or derivative of this software   *
 * made or distributed by the recipient and are to be affixed to any  *
 * copy of software made or distributed by the recipient that         *
 * contains a copy or derivative of this software.                    *
 *                                                                    *
 * Based on SLAC Software Notices, Set 4                              *
 * OTT.002a, 2004 FEB 03                                              *
 **********************************************************************/



/**********************************************************************
 *                               NOTICE                               *
 * Creative endeavors depend on the lively exchange of ideas. There   *
 * are laws and customs which establish rights and responsibilities   *
 * for authors and the users of what authors create.  This notice     *
 * is not intended to prevent you from using the software and         *
 * documents in this package, but to ensure that there are no         *
 * misunderstandings about terms and conditions of such use.          *
 *                                                                    *
 * Please read the following notice carefully.  If you do not         *
 * understand any portion of this notice, please seek appropriate     *
 * professional legal advice before making use of the software and    *
 * documents included in this software package.  In addition to       *
 * whatever other steps you may be obliged to take to respect the     *
 * intellectual property rights of the various parties involved, if   *
 * you do make use of the software and documents in this package,     *
 * please give credit where credit is due by citing this package,     *
 * its authors and the URL or other source from which you obtained    *
 * it, or equivalent primary references in the literature with the    *
 * same authors.                                                      *
 *                                                                    *
 * Some of the software and documents included within this software   *
 * package are the intellectual property of various parties, and      *
 * placement in this package does not in any way imply that any       *
 * such rights have in any way been waived or diminished.             *
 *                                                                    *
 * With respect to any software or documents for which a copyright    *
 * exists, ALL RIGHTS ARE RESERVED TO THE OWNERS OF SUCH COPYRIGHT.   *
 *                                                                    *
 * Even though the authors of the various documents and software      *
 * found here have made a good faith effort to ensure that the        *
 * documents are correct and that the software performs according     *
 * to its documentation, and we would greatly appreciate hearing of   *
 * any problems you may encounter, the programs and documents any     *
 * files created by the programs are provided **AS IS** without any   *
 * warranty as to correctness, merchantability or fitness for any     *
 * particular or general use.                                         *
 *                                                                    *
 * THE RESPONSIBILITY FOR ANY ADVERSE CONSEQUENCES FROM THE USE OF    *
 * PROGRAMS OR DOCUMENTS OR ANY FILE OR FILES CREATED BY USE OF THE   *
 * PROGRAMS OR DOCUMENTS LIES SOLELY WITH THE USERS OF THE PROGRAMS   *
 * OR DOCUMENTS OR FILE OR FILES AND NOT WITH AUTHORS OF THE          *
 * PROGRAMS OR DOCUMENTS.                                             *
 **********************************************************************/

/**********************************************************************
 *                                                                    *
 *                           The IUCr Policy                          *
 *      for the Protection and the Promotion of the STAR File and     *
 *     CIF Standards for Exchanging and Archiving Electronic Data     *
 *                                                                    *
 * Overview                                                           *
 *                                                                    *
 * The Crystallographic Information File (CIF)[1] is a standard for   *
 * information interchange promulgated by the International Union of  *
 * Crystallography (IUCr). CIF (Hall, Allen & Brown, 1991) is the     *
 * recommended method for submitting publications to Acta             *
 * Crystallographica Section C and reports of crystal structure       *
 * determinations to other sections of Acta Crystallographica         *
 * and many other journals. The syntax of a CIF is a subset of the    *
 * more general STAR File[2] format. The CIF and STAR File approaches *
 * are used increasingly in the structural sciences for data exchange *
 * and archiving, and are having a significant influence on these     *
 * activities in other fields.                                        *
 *                                                                    *
 * Statement of intent                                                *
 *                                                                    *
 * The IUCr's interest in the STAR File is as a general data          *
 * interchange standard for science, and its interest in the CIF,     *
 * a conformant derivative of the STAR File, is as a concise data     *
 * exchange and archival standard for crystallography and structural  *
 * science.                                                           *
 *                                                                    *
 * Protection of the standards                                        *
 *                                                                    *
 * To protect the STAR File and the CIF as standards for              *
 * interchanging and archiving electronic data, the IUCr, on behalf   *
 * of the scientific community,                                       *
 *                                                                    *
 * * holds the copyrights on the standards themselves,                *
 *                                                                    *
 * * owns the associated trademarks and service marks, and            *
 *                                                                    *
 * * holds a patent on the STAR File.                                 *
 *                                                                    *
 * These intellectual property rights relate solely to the            *
 * interchange formats, not to the data contained therein, nor to     *
 * the software used in the generation, access or manipulation of     *
 * the data.                                                          *
 *                                                                    *
 * Promotion of the standards                                         *
 *                                                                    *
 * The sole requirement that the IUCr, in its protective role,        *
 * imposes on software purporting to process STAR File or CIF data    *
 * is that the following conditions be met prior to sale or           *
 * distribution.                                                      *
 *                                                                    *
 * * Software claiming to read files written to either the STAR       *
 * File or the CIF standard must be able to extract the pertinent     *
 * data from a file conformant to the STAR File syntax, or the CIF    *
 * syntax, respectively.                                              *
 *                                                                    *
 * * Software claiming to write files in either the STAR File, or     *
 * the CIF, standard must produce files that are conformant to the    *
 * STAR File syntax, or the CIF syntax, respectively.                 *
 *                                                                    *
 * * Software claiming to read definitions from a specific data       *
 * dictionary approved by the IUCr must be able to extract any        *
 * pertinent definition which is conformant to the dictionary         *
 * definition language (DDL)[3] associated with that dictionary.      *
 *                                                                    *
 * The IUCr, through its Committee on CIF Standards, will assist      *
 * any developer to verify that software meets these conformance      *
 * conditions.                                                        *
 *                                                                    *
 * Glossary of terms                                                  *
 *                                                                    *
 * [1] CIF:  is a data file conformant to the file syntax defined     *
 * at http://www.iucr.org/iucr-top/cif/spec/index.html                *
 *                                                                    *
 * [2] STAR File:  is a data file conformant to the file syntax       *
 * defined at http://www.iucr.org/iucr-top/cif/spec/star/index.html   *
 *                                                                    *
 * [3] DDL:  is a language used in a data dictionary to define data   *
 * items in terms of "attributes". Dictionaries currently approved    *
 * by the IUCr, and the DDL versions used to construct these          *
 * dictionaries, are listed at                                        *
 * http://www.iucr.org/iucr-top/cif/spec/ddl/index.html               *
 *                                                                    *
 * Last modified: 30 September 2000                                   *
 *                                                                    *
 * IUCr Policy Copyright (C) 2000 International Union of              *
 * Crystallography                                                    *
 **********************************************************************/

#ifndef CBF_HDF5_H
#define CBF_HDF5_H

#ifdef __cplusplus

extern "C" {

#endif


#include <hdf5.h>
#include "cbf.h"
#include "cbf_tree.h"
#include <string.h>
#ifdef CBF_USE_ULP
#include <stdint.h>
#ifndef UINT64_MAX
#define NO_UINT64_TYPE
#endif
#endif
    
    
#define CBF_H5_COLUMN_GROUP       0x00
#define CBF_H5_COLUMN_DATASET     0x01
#define CBF_H5_COLUMN_ATTRIBUTE   0x02
#define CBF_H5_COLUMN_MAP_AXES    0x04
#define CBF_H5_COLUMN_PATH        0x08
#define CBF_H5_TEXT               0x10
#define CBF_H5_FLOAT              0x20
#define CBF_H5_INTEGER            0x40
#define CBF_H5_PRIMARY           0x100
#define CBF_H5_TERMINATE        0x1000
#define CBF_H5_SPECIAL          0x2000
#define CBF_H5_ARRAY            0x4000
#define CBF_H5_LINK             0x8000  /* should appear both in the special
field of the target and the dsorat
field of the source */
#define CBF_H5_MORE             0x10000 /* more mappings of same column follow
field of the target and the dsorat
field of the source */
    
    
    
    /** return the maximum of two numeric values */
#define cbf_max(a,b) ((a)>(b)?(a):(b))    
    
    /****************************************************************
     The following section of code is extracted from J. Sloan's
     cbf_hdf5_common.h
     ****************************************************************/

#define CBF_H5FAIL ((hid_t)(-1))
    
	/* Function to check validity of a HDF5 identifier. */
	int cbf_H5Ivalid(const hid_t ID);

	/* find/create/free a HDF5 group if it's valid & possibly set the ID to an invalid identifier
     can write requireGroup function as {if (!find(group)) create(group); return group;} */

	int cbf_H5Gcreate(const hid_t location, hid_t * const group, const char * const name);

	int cbf_H5Grequire(const hid_t location, hid_t * const group, const char * const name);

	int cbf_H5Gfree(const hid_t ID);

	/* Open/close a HDF5 file if it's valid & possibly set the ID to an invalid identifier */

	int cbf_H5Fopen(hid_t * const file, const char * const name);

	int cbf_H5Fclose(const hid_t ID);

	/* Attributes */
    
	int cbf_H5Arequire_cmp
    (const hid_t ID,
     const char * const name,
     const int rank,
     const hsize_t * const dim,
     const hid_t type,
     const void * const value,
     void * const buf,
         int (*cmp)(const void *, const void *, size_t));

	int cbf_H5Arequire_cmp2
		(const hid_t ID,
		const char * const name,
		const int rank,
		const hsize_t * const dim,
		const hid_t fileType,
		const hid_t memType,
		const void * const value,
		void * const buf,
		int (*cmp)(const void *, const void *, size_t));
	
    int cbf_H5Arequire_cmp2_ULP
        (const hid_t ID,
         const char * const name,
         const int rank,
         const hsize_t * const dim,
         const hid_t fileType,
         const hid_t memType,
         const void * const value,
         void * const buf,
         int (*cmp)(const void *, const void *, size_t, const void *),
         const void * const cmp_params);

	int cbf_H5Arequire_string
		(const hid_t location,
		const char * const name,
		const char * const value);

	/*  find/create/free hdf5 datasets without directly using hdf5 API */

	int cbf_H5Dcreate
		(const hid_t location,
		hid_t * const dataset,
		const char * const name,
		const int rank,
		const hsize_t * const dim,
		const hsize_t * const max,
		const hsize_t * const chunk,
		const hid_t type);

    /* Look for a dataset with the given properties. */
     
     
	int cbf_H5Dfind
        (const hid_t location,
         hid_t * const dataset,
         const char * const name,
         const int rank,
         const hsize_t * const dim,
         const hsize_t * const max,
         const hsize_t * const chunk,
         const hid_t type);
	
    int cbf_H5Dfind2
		(const hid_t location,
		hid_t * const dataset,
		const char * const name,
		const int rank,
		const hsize_t * const max,
		hsize_t * const buf,
		const hid_t type);

	int cbf_H5Drequire
			(const hid_t location,
			 hid_t * const dataset,
			 const char * const name,
			 const int rank,
			 const hsize_t * const max,
			 const hsize_t * const chunk,
			 hsize_t * const buf,
			 const hid_t type);

	int cbf_H5Dinsert
			(const hid_t dataset,
			 const hsize_t * const offset,
			 const hsize_t * const stride,
			 const hsize_t * const count,
			 hsize_t * const buf,
			 const void * const value,
			 const hid_t type);

	int cbf_H5Dset_extent(const hid_t dataset, const hsize_t * const dim);

	int cbf_H5Dwrite
        (const hid_t dataset,
        const hsize_t * const offset,
        const hsize_t * const stride,
        const hsize_t * const count,
        const void * const value);

	int cbf_H5Dwrite2
		(const hid_t dataset,
		const hsize_t * const offset,
		const hsize_t * const stride,
		const hsize_t * const count,
		const void * const value,
		const hid_t type);

	int cbf_H5Dread
		(const hid_t dataset,
		const hsize_t * const offset,
		const hsize_t * const stride,
		const hsize_t * const count,
        void * const value);

	int cbf_H5Dread2
		(const hid_t dataset,
		const hsize_t * const offset,
		const hsize_t * const stride,
		const hsize_t * const count,
		void * const value,
		const hid_t type);

	int cbf_H5Drequire_scalar_F64LE
		(const hid_t location,
		hid_t * const dataset,
		const char * const name,
        const double value);

	int cbf_H5Drequire_scalar_F64LE2
		(const hid_t location,
		hid_t * const dataset,
		const char * const name,
		const double value,
		int (*cmp)(const void *, const void *, size_t)
        );

	int cbf_H5Drequire_scalar_F64LE2_ULP
    (const hid_t location,
     hid_t * const dataset,
     const char * const name,
     const double value,
     int (*cmp)(const void *, const void *, size_t, const void *),
     const void * const cmp_params);

    int cbf_H5Drequire_flstring
		(const hid_t location,
		hid_t * const dataset,
		const char * const name,
		const char * const value);

	int cbf_H5Dfree(const hid_t ID);

	/* Custom HDF5 types - to get the correct string type for datasets in a consistent way */

	int cbf_H5Tcreate_string(hid_t * type, const size_t len);

	int cbf_H5Tfree(const hid_t ID);

	/* HDF5 dataspace functions: I need a uniform method of creating data spaces to ensure correct operation of comparison functions */

	int cbf_H5Screate
		(hid_t * const ID,
		const int rank,
		const hsize_t * const dim,
		const hsize_t * const max);

	int cbf_H5Sfree(const hid_t ID);


    /****************************************************************
     End of section of code extracted from J. Sloan's
     cbf_hdf5_common.h
     ****************************************************************/
    /****************************************************************
     The following section of code is extracted from J. Sloan's
     config.h
     ****************************************************************/
    
    struct FILE;

	extern const int cbf_configError_success;

    /** \brief Convert a parse error to a descriptive string. */
    const char * cbf_config_strerror(const int error);

    /* Opaque type for a collection of configuration items */
    struct cbf_config_t;
	typedef struct cbf_config_t cbf_config_t;

	/** \brief Obtain a new handle for some configuration settings. */
	cbf_config_t * cbf_config_create();

	/** \brief Free any heap memory associated with the given cbf_hdf5_configItemVectorhandle object. */
	void cbf_config_free(const cbf_config_t * const vector);

	/** \brief Read a minicbf configuration file into the given handle, writing errors to <code>logfile</code>. */
	int cbf_config_parse(FILE * const configFile, FILE * const logFile, cbf_config_t * const vec);

    /****************************************************************
     End of section of code extracted from J. Sloan's
     config.h
     ****************************************************************/


    /* Attribute type definition, agrees with CBFlib data convensions */
    
	typedef struct cbf_name_value_pair_def
	{
		const char * name;
		const void * value;
	} cbf_name_value_pair;
    

    
    /* Write a CBF value into a NeXus file
     Will add a piece of data with a given name to /entry/group@groupNXclass/subGroup@subGroupNXclass/name */
    
    
#define cbf_h5failneg(x,code) {int err; err = (x); if (err < 0) {return (code);}}
#define cbf_h5onfailneg(x,code,y) {int err; err = (x); if (err < 0) {{y;} return (code);}}
#define cbf_h5reportneg(x,code,cerr) \
{int err; if (!(cerr)) {err = (x); if (err < 0) {(cerr)|=code;}}}
#define cbf_reportnez(x,cerr) \
{int err; if (!(cerr)) {err = (x); (cerr)|=err;}}

#define reportFail(f, errorCode, errorVar) \
do { \
if (CBF_SUCCESS == errorVar && !(f)) { \
errorVar |= (errorCode); \
fprintf(stderr, "%s:%d: '" #f "' failed.\n", __FILE__, __LINE__); \
} \
} while (0)

#define cbf_reportFail(f, errorVar) \
do { \
if (CBF_SUCCESS == errorVar) { \
const int errorCode = (f); \
if (CBF_SUCCESS != errorCode) \
errorVar |= errorCode; \
} \
} while (0)

    
#ifndef H5_VERS_MAJOR
#define H5_VERS_MAJOR 0
#endif
    
#ifndef H5_VERS_MINOR
#define H5_VERS_MINOR 0
#endif
    
    
#if (H5_VERS_MAJOR>1)||((H5_VERS_MAJOR==1)&&(H5_VERS_MINOR>=8))
    
#define H5Acreatex(loc_id,name,type_id,space_id,acpl_id) \
H5Acreate2(loc_id,name,type_id,space_id,acpl_id,H5P_DEFAULT)
#define H5Dcreatex(loc_id,name,type_id,space_id,dcpl_id) \
H5Dcreate2(loc_id,name,type_id,space_id,H5P_DEFAULT,dcpl_id,H5P_DEFAULT)
#define H5Gcreatex(loc_id,name) \
H5Gcreate2(loc_id,name,H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT)
#define H5Gopenx(loc_id,name) H5Gopen2(loc_id,name,H5P_DEFAULT)
    
#else
    
#error HDF5 Version >= 1.8 Required
    
#endif
    
    /* CBF Bookmark */
    
    typedef struct {
        const char * datablock;
        const char * category;
        const char * column;
        unsigned int row;
        int haverow;
    } cbf_bookmark;
    
    /* CBF Fast Bookmark */
    
    typedef struct {
        cbf_node *node;
        int row;
    } cbf_fast_bookmark;
    
    
    /* H5File structure */
    
    typedef struct
    {
        int   rwmode;  /* 0 for read-only, 1 for read-write */
		unsigned int slice; /* The slice within the HDF5 data arrays where data will be added */
		hid_t hfile;   /* The HDF5 file */
		hid_t nxid;    /* /entry@NXentry */
		hid_t nxdata; /* /entry/data@NXdata */
		hid_t nxsample; /* /entry/sample@NXsample group */
		hid_t nxinst;  /* /entry/instrument@NXinstrument */
		hid_t nxdetector; /* /entry/instrument/detector@NXdetector */
		hid_t nxmonochromator;  /* /entry/instrument/monochromator@NXmonochromator */
        hid_t nxgoniometer;  /* /entry/instrument/goniometer@NXgoniometer */
        hid_t rootid;  /* The root CBF database group */
        hid_t dbid;    /* The current datablock in the CBF */
        hid_t sfid;    /* The current saveframe in the current datablock or -1 */
        hid_t catid;   /* The current category */
        hid_t colid;   /* The current column */
        hid_t curnxid; /* The current NeXus group */
        hid_t dataid;  /* The NeXus NXdata group */
		/* Names of various groups, used to construct paths to the axes */
		const char * nxid_name;
		const char * nxdetector_name;
		/* Flags for various options */
        int flags;
#ifdef CBF_USE_ULP
		/* Parameters controlling floating point comparisons */
		int cmp_double_as_float;
		unsigned int float_ulp;
#ifndef NO_UINT64_TYPE
		uint64_t double_ulp;
#endif
#endif
        cbf_bookmark
        bookmark;/* Read bookmark to save names for paths */

    }
    cbf_h5handle_struct;
    
    typedef cbf_h5handle_struct *cbf_h5handle;
    
    typedef struct
    {
        cbf_handle handle;
        cbf_h5handle h5handle;
        hid_t parent_id;
        haddr_t parent_addr;
        const char * grand_parent_name;
        const char * parent_name;
        size_t capacity;
        size_t path_size;
        hid_t *hid_path;
        haddr_t *haddr_path;
        cbf_bookmark bookmark; /* bookmark in the CBF */
        int incbf;     /* set to 1 when we have descended
                        into a NeXus NXcbf    */
        int incbfdb;   /* set to 1 when we have descended
                        into a NeXus NXcbfdb  */
        int incbfcat;  /* set to 1 when we have descended
                        into a NeXus NXcbfcat */
        int incbfcol;  /* set to 1 when we have descended
                        into a NeXus NXcbfcol */
        int innexus;   /* set to 1 shen we have descended
                        into a NeXus NXexntry */
    }
    cbf_h5Ovisit_struct;
    
	typedef cbf_h5Ovisit_struct *cbf_h5Ovisithandle;
    
    /* Ensure I have a file to do stuff with. */
	int cbf_h5handle_require_file(const cbf_h5handle handle, const char * name);
    
    /* Ensure I have a top-level NXentry group in the handle */
	int cbf_h5handle_require_entry(const cbf_h5handle handle, hid_t * group, const char * name);
    
    /* Ensure I have an NXsample group in the handle called 'sample' below the entry */
	int cbf_h5handle_require_sample(const cbf_h5handle handle, hid_t * group);
    
    /* Ensure I have an NXinstrument group in the handle called 'instrument' */
	int cbf_h5handle_require_instrument(const cbf_h5handle handle, hid_t * group);
    
    /* Ensure I have a detector with the given name in the hdf5 handle */
    int cbf_h5handle_require_detector(const cbf_h5handle handle, hid_t * group,
                                      const char * const name);
    
    /* Ensure I have a monochromator in the hdf5 handle */
	int cbf_h5handle_require_monochromator(const cbf_h5handle handle, hid_t * group);
    
    /* Create a dotted CBF location string
     returns a newly allocated string that
     must be freed */
    
    int cbf_location_string(const char* datablock,
                            const char* category,
                            const char* column,
                            unsigned int row,
                            char * * stringout);
    
    /* Conatenate two strings, returning a newly allocated string */
    
    int cbf_strcat(const char * string1, const char * string2,
                   char * * stringout);
    
    /* Either open or create a NeXus group*/
    
    int cbf_require_nxgroup(cbf_h5handle h5handle,
                            const char * nxgroup,
                            const char * nxclass,
                            hid_t parent_id,
                            hid_t * groupid);

    
    /* get an axis vector and offset */
    
    
    int cbf_get_axis_vector_and_offset(cbf_handle handle,
                                       const char *axis_id,
                                       double vector[3],
                                       double offset[3]);
    
    /* Compute the cross-product of 2 3-vectors */
    
    int cbf_cross_product(double vecin1[3],
                          double vecin2[3],
                          double vecout[3] );
    
    /* compute the L2 norm of a 3-vector */
    
    double cbf_norm(double vector[3]);
    
    /* compute the product of a scalar and a vector */
    
    int cbf_scalar_product(double scalar, double vecin[3], double vecout[3]);
    
    
    /* Apply a matrix to a vector */
    
    int cbf_apply_matrix(double matrix[3][3], double vecin[3], double vecout[3]);
    
    /* compute the transform from CBF vectors to NeXus vectors
     Use the transpose to transfrom from NeXus vectors to CBF*/
    
    int cbf_get_NX_axis_transform(cbf_handle handle,
                                  double matrix [3][3]);
    
    
    /* Write the HDF5 version of the NeXus axis definitions, if
     the original CBF had axis definitions */
    
    int cbf_write_h5nxaxes(cbf_handle handle, cbf_h5handle h5handle);
    
    
    /* apply a double vector attribute to a group or dataset */
    
    int cbf_apply_h5vector_attribute(hid_t hid,
                                     const char* attribname,
                                     const double* attribvec,
                                     const size_t dimension,
                                     int errorcode);
    
    /* apply a long attribute to a group or dataset */
    
    int cbf_apply_h5longasstr_attribute(hid_t hid,
                                        const char* attribname,
                                        const long attriblong,
                                        int errorcode);
    
    /* apply an integer attribute to a group or dataset as a string */
    
    int cbf_apply_h5intasstr_attribute(hid_t hid,
                                       const char* attribname,
                                       const int attribint,
                                       int errorcode);
    
    /* apply a integer attribute to a group or dataset */
    
    int cbf_apply_h5integer_attribute(hid_t hid,
                                      const char* attribname,
                                      const int attribint,
                                      int errorcode);
    
    /* apply a text attribute to a group or dataset */
    
    int cbf_apply_h5text_attribute(hid_t hid,
                                   const char* attribname,
                                   const char* attribtext,
                                   int errorcode);

    /* apply a text dataset slab to a group
     
     places the specified datasettext in the specified slab of the
     specified datasetname for group hid.  The dataset is created
     if it does not already exist.
     
     The slabs are indexed from 0
     
     */
    
    int cbf_apply_h5text_dataset_slab(hid_t hid,
                                      const char* datasetname,
                                      const char* datasettext,
                                      const hsize_t slab,
                                      int errorcode);
    
    /* apply a text dataset to a group */
    
    int cbf_apply_h5text_dataset(hid_t hid,
                                 const char* datasetname,
                                 const char* datasettext,
                                 int errorcode);
    
    /* add a long dataset slab to a group
     
     places the specified datasetvalue in the specified slab of the
     specified datasetname for group hid.  The dataset is created
     if it does not already exist.
     
     The slabs are indexed from 0
     
     */
    
    int cbf_add_h5long_dataset_slab(hid_t hid,
                                    const char* datasetname,
                                    const long datasetvalue,
                                    const hsize_t slab,
                                    int errorcode);
    
    /* add a long dataset to a group */
    
    int cbf_add_h5long_dataset(hid_t hid,
                               const char* datasetname,
                               const long datasetvalue,
                               int errorcode);
    
    
    /* Write a binary value to an HDF5 file */
    
    int cbf_write_h5binary (cbf_handle handle,
                            cbf_node *column,
                            unsigned int row,
                            cbf_h5handle h5handle);
    
    /* Write an ascii value to an HDF5 file */
    
    int cbf_write_h5ascii (cbf_handle handle,
                           unsigned int row,
                           const char *string,
                           cbf_h5handle h5handle);
    
    /* Write a value to an HDF5 file */
    
    int cbf_write_h5value (cbf_handle handle, cbf_node *column, unsigned int row,
                           cbf_h5handle h5handle);
    
    /* Write a category to an HDF5 file */
    
    int cbf_write_h5category (cbf_handle handle,
                              const cbf_node *category,
                              cbf_h5handle h5handle);
    
    /*  create top-level NXentry */
    
    int cbf_create_NXentry(cbf_h5handle h5handle);
    
    /*  Create an HDF5 Group below NX entry or below curnxid */
    
    int cbf_H5Gcreate_in_handle(cbf_h5handle h5handle,
                                const char * groupname,
                                hid_t * newgroup);
    
    /*  Create an HDF5 NeXus Group below NX entry or below curnxid */
    
    int cbf_H5NXGcreate(cbf_h5handle h5handle,
                        const char * groupname,
                        const char * nxclass,
                        hid_t * newgroup);
    
    /* Require a group below NXentry or below curnxid
     groupname     -- the final path to be used
     group_id      -- optional pointer to the newly opened group
     if NULL, no return and the group will be
     closed
     oldgroupname  -- an optional existing path name or NULL
     to be renamed to new_name if old_name exists
     and if groupname does not yet exist
     
     returns 0 for success
     */
    int cbf_H5Grequire_in_handle(const cbf_h5handle h5handle,
                                 const char * groupname,
                                 hid_t * group_id,
                                 const char * oldgroupname);
    
    /* Require NeXus group below NXentry or below curnxid
     groupname     -- the final path to be used
     group_id      -- optional pointer to the newly opened group
     if NULL, no return and the group will be
     closed
     oldgroupname  -- an optional existing path name or NULL
     to be renamed to new_name if old_name exists
     and if groupname does not yet exist
     
     returns 0 for success
     */
    int cbf_H5NXGrequire_in_handle(const cbf_h5handle h5handle,
                                   const char * groupname,
                                   const char * nxclass,
                                   hid_t * group_id,
                                   const char * oldgroupname);
    
    /* Free an H5File handle */
    
    int cbf_free_h5handle(cbf_h5handle h5handle);
    
    /* Make an (empty) H5File handle */
    
    int cbf_make_h5handle(cbf_h5handle *h5handle);
    
    /* Close the current saveframe in an HDF5 file */
    
    int cbf_close_h5saveframe (cbf_h5handle h5handle);
    
    /* Write a saveframe name to an HDF5 file
     Make a new group of NeXus class NXcifsf in the NXcif current datablock
     */
    
    int cbf_write_h5saveframename (const cbf_node *saveframename,
                                   cbf_h5handle h5handle);
    
    /* Write a datablock name to an HDF5 file
     Make a new group of NeXus class NXcifdb in the NXcif class root
     */
    
    int cbf_write_h5datablockname (const cbf_node *datablock, cbf_h5handle h5handle);
    
    /* Write a node to an HDF5 file */
    
    int cbf_write_h5node (cbf_handle handle, const cbf_node *node,
                          const cbf_h5handle h5handle);
    
    /* Create an H5File handle */
    
    int cbf_create_h5handle(cbf_h5handle *h5handle,
							const char * h5filename);
    
	/* Create an HDF5 File handle without adding an NXcbf group to it */
	int cbf_create_h5handle2(cbf_h5handle *h5handle,const char * h5filename);
    
    /*  Write cbf to HDF5 file hfile */
    
	int cbf_write_h5file (cbf_handle handle, cbf_h5handle h5handle, int flags);
    
	/* Write a cbf file to a nexus file */
	int cbf_write_cbf_h5file
			(cbf_handle handle,
			 cbf_h5handle h5handle);

	/* Write a minicbf file to a nexus file */
	int cbf_write_minicbf_h5file (cbf_handle handle, cbf_h5handle h5handle, const cbf_config_t * const axisConfig);

    /* Open an HDF5 File handle */
    
    int cbf_open_h5handle(cbf_h5handle *h5handle,
                          const char * h5filename);
    
    /* Convert an HDF5 typeclass to a string
     and flag for atomic or not
     copies up to n-1 characters of the
     type string to buffer*/
    
    int cbf_h5type_class_string(H5T_class_t type_class,
                                char * buffer,
                                int * atomic, size_t n );
    
    
    /* Store an HDF5 Dataset in CBF handle, using
     category categoryname, ...*/
    
    int cbf_h5ds_store(cbf_handle handle, haddr_t parent,
                       const char * parent_name,
                       const int target_row,
                       const char * categoryname, hid_t obj_id,
                       hid_t space, hid_t type,
                       const char * name,
                       const int readattrib,
                       void ** value);
    
    
    /* Callback routine for objects in a group */
    
    
    herr_t cbf_object_visit(hid_t loc_id, const char *name,
                            const H5L_info_t *info,
                            void *op_data);
    
    
    /* Read an HDF5 file */
    
    int cbf_read_h5file(const cbf_handle handle,
                        const cbf_h5handle h5handle,
                        const int flags);
    
    /* get a fast bookmark from the current information in a cbf handle */
    
    int cbf_get_fast_bookmark(const cbf_handle handle, cbf_fast_bookmark * bookmark);
    
    /* go to a fast bookmark in a cbf handle */
    
    int cbf_goto_fast_bookmark(const cbf_handle handle, const cbf_fast_bookmark bookmark);
    
    
    /* go to a bookmark in the cbf handle */
    
    int cbf_goto_bookmark(const cbf_handle handle, const cbf_bookmark bookmark);
    
    /* get a bookmark from the current information in a cbf handle */
    
    int cbf_get_bookmark(const cbf_handle handle, cbf_bookmark * bookmark);
    
    int cbf_map_h5value(
                        const char * const name, const char * const value,
                        const char * const group, const char * const groupNXclass,
                        const char * const subGroup, const char * const subGroupNXclass,
                        const size_t attrc, const cbf_name_value_pair * const attrv,
                        cbf_h5handle h5handle);

    
    
#ifdef __cplusplus

}

#endif


#endif /* CBF_HDF5_H */
