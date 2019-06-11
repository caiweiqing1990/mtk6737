#include "StdAfx.h"
#include "OptimizeWave.h"
 
 
#define DEFAULT_LENGTH    2512//56
#define DEFAULT_SHIFT     128//32
#define DEFAULT_MULTIPLE  1.0
#define DEFAULT_SMOOTHING 1.0
#define DEFAULT_AGCKK     1.0
 
#define		MSG_PROGRESS_UPDATE	WM_USER + 0x800
#define		MSG_PROGRESS_COMPLETE	WM_USER + 0x801
 
COptimizeWave::COptimizeWave(void)
{
	m_hWnd = NULL;
	m_bCancel = FALSE;
}
 
 
COptimizeWave::~COptimizeWave(void)
{
}
 
void COptimizeWave::SetRecvHWND(HWND hWnd)
{
	m_hWnd = hWnd;
}
 
void COptimizeWave::Cancel()
{
	m_bCancel = TRUE;
}
 
HRESULT COptimizeWave::OptimizeWave(LPCSTR strSrcFile)
{
	m_bCancel = FALSE;
	short *is, *ix;
	int  m0, i, j;
	int  length = 0;
 
	int  shift = 0, lhalf, lpow2, half_pow2;
	int  nread, noffile = 0;
	double smul = 0.0;
	double lambda = 0.0;
	double ar, ai, power;
	double *win, *frame, *noise, *pre;
	double *rev_win;
	char *argin;
	double kk;
 
 
	FILE *srcfd, *dstfd;
 
	char strTempPCMFile[] = "TempPcm.pcm";
	srcfd = fopen( strSrcFile,"rb");
	dstfd = fopen( strTempPCMFile, "wb");
 
	fseek( srcfd, 0, SEEK_END );
	int len = ftell( srcfd );
	fseek( srcfd, 0, SEEK_SET );
 
	int count = 0;
	int pos =  0;
 
	/*----------------------- trim variables ----------------------*/
	if (0   == length) length = DEFAULT_LENGTH;
	if (0   == shift)  shift  = DEFAULT_SHIFT;
	if (0.0 == smul)   smul = DEFAULT_MULTIPLE;
	if (0.0 == lambda) lambda = DEFAULT_SMOOTHING;
 
	m0 = 0;
	lpow2 = 1;
	lhalf = ((length + 1)/2);
	length = lhalf + lhalf;    /* rounding */
	while(lpow2 < length) {
		lpow2 += lpow2;
		++m0;
	}
	half_pow2 = lpow2/2;
 
	/*------------------ allocate memory ------------------*/
	frame = xd_realloc(NULL, lpow2+2);
	noise = xd_realloc(NULL, half_pow2+1);
	win   = xd_realloc(NULL, length);
	rev_win = xd_realloc(NULL, shift + shift);
	pre     = xd_realloc(NULL, shift);
 
	is = (short *)xx_realloc(NULL, length * sizeof(short));
	ix = (short *)xx_realloc(NULL, shift * sizeof(short));
 
	/*----------------- setup windows ------------------*/
	for (i = 0; i < length; ++i)
		win[i] = 0.5 - 0.5 * cos(PI * 2.0 * (double)i / (double)length);
	for (i = -shift; i < shift; ++i)
		rev_win[i+shift]
	= (0.5 + 0.5 * cos(PI * (double)i/(double)shift)) / win[i+lhalf];
 
	/*----------------- initialize noise spectrum ------------*/
	nread = fread(is, sizeof(*is), length, srcfd);
	multirr(length, is, win, frame);
	for (i = length; i < lpow2; ++i) frame[i] = 0.0;
	rfft(m0, frame);
	for (i = j = 0; j <= lpow2; ++i, j += 2) {
		noise[i] = sqrt(frame[j] * frame[j] + frame[j+1] * frame[j+1]);
	}
	for (i = 0; i < shift; ++i)
		pre[i] = 0.0;
 
	nread = getfirst(length, lhalf-shift, is, srcfd);
	while(0 != nread && !m_bCancel) {
		multirr(length, is, win, frame);
		for (i = length; i < lpow2; ++i)
			frame[i] = 0.0;
		rfft(m0, frame);
		for (i = j = 0; i <= lpow2; i += 2, ++j) {
			ar = frame[i];
			ai = frame[i+1];
			power   = sqrt(ar * ar + ai * ai + 1.0e-30);
			ar   /= power;
			ai   /= power;
#if 0	    
			if (power < noise[j] * smul) {
				noise[j] = noise[j] * lambda + (1.0 - lambda) * power;
				power = 0.0;
			}else{
				power -= noise[j] * smul;
			}
#else	//改为公式9
			kk = pow(power, 0.4) - 0.9 * pow(noise[j], 0.4);
			if (kk < 0) kk = 0;
			kk = pow(kk, (1/0.4));
			power = kk;	
#endif	    
			frame[i]   = ar * power * DEFAULT_AGCKK;
			frame[i+1] = ai * power * DEFAULT_AGCKK;
		}
		irfft(m0, frame);
		for (i = 0; i < shift; ++i) {
			ar = pre[i] + frame[i+lhalf-shift] * rev_win[i];
			ix[i] = (short)ar;
		}
		for (i = 0; i < shift; ++i) {
			pre[i] = frame[i+lhalf] * rev_win[i+shift];
		}
		fwrite(ix, sizeof(*ix), shift, dstfd);
		count = count + sizeof(*ix)*shift;
		if ( count>= (len/100))
		{
			if ( m_hWnd != NULL )
			{
				//PostMessage( m_hWnd, MSG_PROGRESS_UPDATE, pos++, NULL );
			}
			
			count = 0;
		}
		nread = rdframe(length, shift, is, srcfd);
	}
 
	fclose(srcfd);
	fclose(dstfd);
	if ( !m_bCancel)
	{
		char strTempWavFile[] = "TempPcm.wav";
		if (MakWav( strTempPCMFile,strTempWavFile ))
		{
			DeleteFileA(strSrcFile);
			CopyFileA(strTempWavFile, strSrcFile, FALSE);
		}
		//PostMessage( m_hWnd, MSG_PROGRESS_COMPLETE, 0, NULL);
		return S_OK;
	}
	return E_FAIL;
}
 
double *COptimizeWave::xd_realloc(double *ptr, unsigned nitems)
{
	double *tmp;
 
	if (ptr == NULL)
		tmp = (double *)malloc(nitems * sizeof(*ptr));
	else
		tmp = (double *)realloc(ptr, nitems * sizeof(*ptr));
	if (NULL == tmp) {
		fprintf(stderr, "xd_realloc failed !!\n");
		exit(0);
	}
	return tmp;
}
 
void *COptimizeWave::xx_realloc(char *ptr, unsigned size)
{
	void *tmp;
	if (ptr == NULL)
		tmp = (void *)malloc(size * sizeof(*ptr));
	else
		tmp = (void *)realloc(ptr, size * sizeof(*ptr));
	if (NULL == tmp) {
		fprintf(stderr, "xx_realloc failed !!\n");
		exit(0);
	}
	return tmp;
}
 
void COptimizeWave::multirr(int length, short *id, double *win, double *frame)
{
	while(--length >= 0) *frame++ = (double)*id++ * *win++;
}
 
//实序列快速傅里叶变换
void COptimizeWave::rfft(int m0, double *x)
{
	int nn, nn2, i, j;
	double d, ti0, tr0, ti1, tr1, ac, as;
	double sstep, cstep, s, c, ww;
 
	nn = 1 << m0;
	nn2 = nn/2;
 
	cfftall(m0-1, x, 1.0);
	d   = PI * 2.0 / (double)nn;
	cstep = cos(d);
	sstep = sin(d);
 
	c = cstep;
	s = sstep;
 
	for (i = 2; i < nn2; i += 2) {
		j = nn - i;
		tr0 = (x[i]   + x[j])   * 0.5;
		ti0 = (x[i+1] - x[j+1]) * 0.5;
		tr1 = (x[i+1] + x[j+1]) * 0.5;
		ti1 = (x[j]   - x[i])   * 0.5;
 
		ac = tr1 * c - ti1 * s;
		as = ti1 * c + tr1 * s;
 
		x[j]   =  tr0 - ac;
		x[j+1] = -ti0 + as;
		x[i]   =  tr0 + ac;
		x[i+1] =  ti0 + as;
 
		ww = c * cstep - s * sstep;
		s  = s * cstep + c * sstep;
		c  = ww;
	}
	tr0     = x[0];
	tr1     = x[1];
	x[0]    = tr0 + tr1;
	x[1]    = 0.0;
	x[nn]   = tr0 - tr1;
	x[nn+1] = 0.0;
}
 
void COptimizeWave::cfftall(int m0, double *x, double ainv)
{
	int    i, j, lm, li, k, lmx, lmx2, np, lix;
	double  temp1, temp2;
	double  c, s, csave, sstep, cstep;
	double  c0, s0, c1, s1;
 
	lmx = 1 << m0;
 
	csave = PI * 2.0 / (double)lmx;
	cstep = cos(csave);
	sstep = sin(csave);
 
	lmx += lmx;
	np   = lmx;
 
	/*----- fft butterfly numeration */
	for (i = 3; i <= m0; ++i) {
		lix = lmx;
		lmx >>= 1;
		lmx2 = lmx >> 1;
		c = cstep;
		s = sstep;
		s0 = ainv * s;
		c1 = -s;
		s1 = ainv * c;
		for (li = 0; li < np; li += lix ) {
			j = li;
			k = j + lmx;
			temp1  = x[j] - x[k];
			x[j]  += x[k];
			x[k]   = temp1;
			temp2  = x[++j] - x[++k];
			x[j]  += x[k];
			x[k]   = temp2;
 
			temp1  = x[++j] - x[++k];
			x[j]  += x[k];
			temp2  = x[++j] - x[++k];
			x[j]  += x[k];
			x[k-1] = c * temp1 - s0 * temp2;
			x[k]   = s0 * temp1 + c * temp2;
 
			j = li + lmx2;
			k = j + lmx;
			temp1  = x[j] - x[k];
			x[j]  += x[k];
			temp2  = x[++j] - x[++k];
			x[j]  += x[k];
			x[k-1] = -ainv * temp2;
			x[k]   =  ainv * temp1;
 
			temp1  = x[++j] - x[++k];
			x[j]  += x[k];
			temp2  = x[++j] - x[++k];
			x[j]  += x[k];
			x[k-1] = c1 * temp1 - s1 * temp2;
			x[k]   = s1 * temp1 + c1 * temp2;
 
		}
		for (lm = 4; lm < lmx2; lm += 2) {
			csave = c;
			c = cstep * c - sstep * s;
			s = sstep * csave + cstep * s;
 
			s0 = ainv * s;
			c1 = -s;
			s1 = ainv * c;
 
			for (li = 0; li < np; li += lix ) {
				j = li + lm;
				k = j + lmx;
				temp1  = x[j] - x[k];
				x[j]  += x[k];
				temp2  = x[++j] - x[++k];
				x[j]  += x[k];
				x[k-1] = c * temp1 - s0 * temp2;
				x[k]   = s0 * temp1 + c * temp2;
 
				j = li + lm + lmx2;
				k = j + lmx;
				temp1  = x[j] - x[k];
				x[j]  += x[k];
				temp2  = x[++j] - x[++k];
				x[j]  += x[k];
				x[k-1] = c1 * temp1 - s1 * temp2;
				x[k]   = s1 * temp1 + c1 * temp2;
			}
		}
		csave = cstep;
		cstep = 2.0 * cstep * cstep - 1.0;
		sstep = 2.0 * sstep * csave;
	}
	if (m0 >= 2)
		for (li = 0; li < np; li += 8) {
			j = li;
			k = j + 4;
			temp1 = x[j] - x[k];
			x[j] += x[k];
			temp2 = x[++j] - x[++k];
			x[j] += x[k];
			x[k-1] = temp1;
			x[k]   = temp2;
			temp1  = x[++j] - x[++k];
			x[j]  += x[k];
			temp2  = x[++j] - x[++k];
			x[j]  += x[k];
			x[k-1] = -ainv * temp2;
			x[k]   =  ainv * temp1;
		}
		for (li = 0; li < np; li += 4) {
			j = li;
			k = j + 2;
			temp1 = x[j] - x[k];
			x[j]  += x[k];
			x[k]   = temp1;
			temp2  = x[++j] - x[++k];
			x[j]  += x[k];
			x[k]   = temp2;
		}
 
		/*----- fft bit reversal */
		lmx = np / 2;
		j = 0;
		for (i = 2; i < np - 2; i += 2) {
			k = lmx;
			while(k <= j) {
				j -= k;
				k >>= 1;
			}
			j += k;
			if ( i < j ) {
				temp1 = x[j];
				x[j] = x[i];
				x[i] = temp1;
				lm = j + 1;
				li = i + 1;
				temp1 = x[lm];
				x[lm] = x[li];
				x[li] = temp1;
			}
		}
		if (ainv == 1.0) return;
 
		temp1 = 1.0 / (double)lmx;
		for (i = 0; i < np; ++i) *x++ *= temp1;
		return;
}
 
int COptimizeWave::getfirst(int length, int offset, short *is, FILE *stream)
{
	int nread;
	rewind(stream);
	nread = length - offset;
	if (nread < 0) return nread;
	while(offset--) *is++ = 0;
	nread = fread(is, sizeof(*is), nread, stream);
	return nread;
}
 
//共轭对称复序列的快速傅里叶反变换
void COptimizeWave::irfft(int m0, double *x)
{
	int nn, i, j;
	double d, ti0, tr0, ti1, tr1, ac, as;
	double sstep, cstep, s, c, ww;
 
	nn = 1 << m0;
 
	d   = PI * 2.0 / (double)nn;
	cstep = cos(d);
	sstep = sin(d);
 
	c = cstep;
	s = sstep;
 
	for (i = 2; i < (j = nn - i); i += 2) {
		tr0 = (x[i]   + x[j])* 0.5;
		ti0 = (x[i+1] - x[j+1]) * 0.5;
		as  = (x[i+1] + x[j+1]) * 0.5;
		ac  = (x[i]   - x[j]) * 0.5;
 
		tr1 = ac * c + as * s;
		ti1 = as * c - ac * s;
 
		x[i]   =  tr0 - ti1;
		x[i+1] =  ti0 + tr1;
		x[j]   =  tr0 + ti1;
		x[j+1] =  tr1 - ti0;
 
		ww = c * cstep - s * sstep;
		s  = s * cstep + c * sstep;
		c  = ww;
	}
	tr0  = x[0] + x[nn];
	tr1  = x[0] - x[nn];
	x[0] = tr0 * 0.5;
	x[1] = tr1 * 0.5;
	cfftall(m0-1, x, -1.0);
}
 
int COptimizeWave::rdframe(int length, int shift, short *is, FILE *stream)
{
	int  i, nread, leneff;
 
	if (length < shift) shift = length;
	leneff = length - shift;
	for (i = 0; i < leneff; ++i) is[i] = is[i + shift];
	nread = fread(&is[leneff], sizeof(*is), shift, stream);
	for (i = nread; i < shift; ++i) is[i+leneff] = 0;
	return(nread);
}
 
BOOL COptimizeWave::MakWav( LPCSTR strpcmFile, LPCSTR strwavFile)
{
	FILE *PCMFile;
	FILE *WavFile;
 
	Int16 temp[160];
	Int32 size;
	Int32 PCMSize=0;
 
	WaveHdr WaveHeader;
 
	WaveHeader.fileID[0] = 'R';
	WaveHeader.fileID[1] = 'I';
	WaveHeader.fileID[2] = 'F';
	WaveHeader.fileID[3] = 'F';
	WaveHeader.fileleth = 0;
	WaveHeader.wavTag[0] = 'W';
	WaveHeader.wavTag[1] = 'A';
	WaveHeader.wavTag[2] = 'V';
	WaveHeader.wavTag[3] = 'E';
 
	//	RiffHdr riffHdr = {"RIFF",0,"WAVE"};
	WaveHeader.FmtHdrID[0] = 'f';
	WaveHeader.FmtHdrID[1] = 'm';
	WaveHeader.FmtHdrID[2] = 't';
	WaveHeader.FmtHdrID[3] = ' ';
 
	WaveHeader.FmtHdrLeth = 0;
 
	//	ChunkHdr FmtHdr = {"fmt ",};
	WaveHeader.DataHdrID[0] = 'd';
	WaveHeader.DataHdrID[1] = 'a';
	WaveHeader.DataHdrID[2] = 't';
	WaveHeader.DataHdrID[3] = 'a';
	WaveHeader.DataHdrLeth = 0;
	//	ChunkHdr DataHdr = {"data",};
	//	ChunkFmtBody FmtBody;
 
	PCMFile = fopen(strpcmFile,"rb");
	WavFile = fopen(strwavFile,"wb");
 
	if(PCMFile==NULL||WavFile==NULL)
		return FALSE;
 
	fseek(WavFile,44L,0);
	size=fread(temp,sizeof(Int16),160,PCMFile);
	while( size > 0 )
	{
		PCMSize += size*2;
		fwrite(temp,sizeof(Int16),size,WavFile);
		fflush( WavFile );
		size=fread(temp,sizeof(Int16),160,PCMFile);
	}
 
	fprintf(stderr,"%s%i\n","PCMSize",PCMSize);
	fclose(PCMFile);
 
	rewind(WavFile);
 
	WaveHeader.fileleth = PCMSize + 32;
	WaveHeader.FmtHdrLeth = 16;
	WaveHeader.BitsPerSample = 16;
	WaveHeader.Channels = 1;
	WaveHeader.FormatTag = 0x0001;
	WaveHeader.SamplesPerSec = 8000;
	WaveHeader.BlockAlign = WaveHeader.Channels * WaveHeader.BitsPerSample /8;
	WaveHeader.AvgBytesPerSec = WaveHeader.BlockAlign * WaveHeader.SamplesPerSec;
	WaveHeader.DataHdrLeth = PCMSize;
 
	fwrite(&WaveHeader,sizeof(WaveHdr),1,WavFile);
	fflush( WavFile );
 
	fclose(WavFile);
	return TRUE;
}
