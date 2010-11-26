/************************************************************************/
/*                                                                      */
/*       Copyright 2010 by Joachim Schleicher and Ullrich Koethe        */
/*                                                                      */
/*    This file is part of the VIGRA computer vision library.           */
/*    The VIGRA Website is                                              */
/*        http://hci.iwr.uni-heidelberg.de/vigra/                       */
/*    Please direct questions, bug reports, and contributions to        */
/*        ullrich.koethe@iwr.uni-heidelberg.de    or                    */
/*        vigra@informatik.uni-hamburg.de                               */
/*                                                                      */
/*    Permission is hereby granted, free of charge, to any person       */
/*    obtaining a copy of this software and associated documentation    */
/*    files (the "Software"), to deal in the Software without           */
/*    restriction, including without limitation the rights to use,      */
/*    copy, modify, merge, publish, distribute, sublicense, and/or      */
/*    sell copies of the Software, and to permit persons to whom the    */
/*    Software is furnished to do so, subject to the following          */
/*    conditions:                                                       */
/*                                                                      */
/*    The above copyright notice and this permission notice shall be    */
/*    included in all copies or substantial portions of the             */
/*    Software.                                                         */
/*                                                                      */
/*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND    */
/*    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES   */
/*    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND          */
/*    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT       */
/*    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,      */
/*    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING      */
/*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR     */
/*    OTHER DEALINGS IN THE SOFTWARE.                                   */
/*                                                                      */
/************************************************************************/


/*                                                          
 *  Opens an Andor .sif file as MultiImageView.             
 *  The width, height and number of images are extracted    
 *  from the ASCII encoded variable length header.          
 *                                                          
 *  Based on the Java-Code from                             
 *  http://rsb.info.nih.gov/ij/plugins/open-sif.html        
 *  written by                                              
 *  L. Stirling Churchman (stirling at stanford.edu)        
 *  Philippe Carl (pcarl at uni-muenster.de)                
 *  Yoshiyuki Arai (arai at phys1.med.osaka-u.ac.jp)        
 *                                                          
 *  Currently tested SIF versions: 4.16.12005.0             
 *                                 4.16.30001.0             
 *                                 4. 6.    3.0             
*/

#ifndef VIGRA_SIFIMPORT_HXX
#define VIGRA_SIFIMPORT_HXX

#include <fstream>
#include <cstring>
#include <vector> 
#include "vigra/multi_array.hxx"

namespace vigra {
 
/********************************************************/
/*                                                      */
/*                   SIFImportInfo                      */
/*                                                      */
/********************************************************/
class SIFImportInfo
{
	public:
		VIGRA_EXPORT SIFImportInfo(const char* filename);
		VIGRA_EXPORT const int width() const;
		VIGRA_EXPORT const int height() const;
		VIGRA_EXPORT const int stacksize() const;
		VIGRA_EXPORT const ptrdiff_t getOffset() const;
		VIGRA_EXPORT const char * getFileName() const;
		VIGRA_EXPORT friend std::ostream& operator<<(std::ostream& os, const SIFImportInfo& info);

	private:
		const char* m_filename;
		int m_width;
		int m_height;
		int m_stacksize;
		ptrdiff_t m_offset;
		int mod;
		int left, right, bottom, top;
		int xbin, ybin, xres, yres;
		int headerlen;
		double readout;
		double temperature1, temperature2;
		long long d;
		std::string cycleTime, temperature, exposureTime, EMGain,
		verticalShiftSpeed, version, model, originalFilename, preAmpGain;	
		size_t filesize;
	
};





VIGRA_EXPORT void readSIF(const SIFImportInfo &info, MultiArrayView<3, float, UnstridedArrayTag> array);

VIGRA_EXPORT std::ostream& operator<<(std::ostream& os, const SIFImportInfo& info);


} // namespace vigra

#endif // VIGRA_SIFIMPORT_HXX
