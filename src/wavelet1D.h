#ifndef WAVELET1D_H
#define WAVELET1D_H

#include "fft/include/fftw.h"
#include "lib/utils.h"
#include "src/wavelet.h"

class CovGrid2D;

class Wavelet1D : public Wavelet {
public:
//Constructors and destructor
  Wavelet1D(Simbox                       * simbox,
            FFTGrid                      * seisCube,
            WellData                    ** wells,
            const std::vector<Surface *> & estimInterval,
            ModelSettings                * modelSettings,
            float                        * reflCoef,
            int                            iAngle);
  Wavelet1D(const std::string & fileName, 
            int                 fileFormat, 
            ModelSettings     * modelSettings, 
            float             * reflCoef,
            float               theta,
            int               & errCode, 
            std::string       & errText);
  Wavelet1D(Wavelet * wavelet);

  virtual ~Wavelet1D();

// Methods that are virtual in Wavelet
  float         findGlobalScaleForGivenWavelet(ModelSettings * modelSettings, 
                                               Simbox        * simbox,
                                               FFTGrid       * seisCube, 
                                               WellData     ** wells);

  float         calculateSNRatioAndLocalWavelet(Simbox        * simbox, 
                                                FFTGrid       * seisCube, 
                                                WellData     ** wells, 
                                                Grid2D       *& shift, 
                                                Grid2D       *& gain, 
                                                ModelSettings * modelSettings,
                                                std::string   & errText, 
                                                int           & error,
                                                Grid2D       *& noiseScaled, 
                                                int             number, 
                                                float           globalScale);

private:
  float         findOptimalWaveletScale(fftw_real               ** synt_seis_r,
                                        fftw_real               ** seis_r,
                                        int                        nWells,
                                        int                        nzp,
                                        const std::vector<float> & wellWeight,
                                        float                    & err,
                                        std::vector<float>       & errWell,
                                        std::vector<float>       & scaleOptWell,
                                        std::vector<float>       & errWellOptScale)   const;

  float         findOptimalWaveletScale(fftw_real               ** synt_seis_r,
                                        fftw_real               ** seis_r,
                                        int                        nWells,
                                        int                        nzp,
                                        const std::vector<float> & wellWeight)   const;

  void          findLocalNoiseWithGainGiven(fftw_real               ** synt_r,
                                            fftw_real               ** seis_r,
                                            int                        nWells,
                                            int                        nzp,
                                            const std::vector<float> & wellWeight,
                                            float                    & err,
                                            std::vector<float>       & errWell, 
                                            std::vector<float>       & errWellOptScale,
                                            std::vector<float>       & scaleOptWell,
                                            Grid2D                   * gain, 
                                            WellData                ** wells, 
                                            Simbox                   * simbox)       const;

  void          estimateLocalGain(const CovGrid2D             & cov,
                                  Grid2D                     *& gain,
                                  const std::vector<float>    & scaleOptWell,
                                  float                         globalScale,
                                  const std::vector<int>      & nActiveData,
                                  Simbox                      * simbox,
                                  WellData                   ** wells,
                                  int                           nWells);
  
  void          estimateLocalShift(const CovGrid2D            & cov,
                                   Grid2D                    *& shift,
                                   const std::vector<float>   & shiftWell,
                                   const std::vector<int>     & nActiveData,
                                   Simbox                     * simbox,
                                   WellData                  ** wells,
                                   int                          nWells);
  
  void          estimateLocalNoise(const CovGrid2D           & cov,
                                   Grid2D                   *& noiseScaled,
                                   float                       globalNoise,
                                   const std::vector<float>  & errWellOptScale,
                                   const std::vector<int>    & nActiveData,
                                   Simbox                    * simbox,
                                   WellData                 ** wells,
                                   int                         nWells);

  void          fillInnWavelet(fftw_real                     * wavelet_r,
                               int                             nzp,
                               float                           dz);

  float         findBulkShift(fftw_real                      * vec_r,
                              float                            dz,
                              int                              nzp,
                              float                            maxShift);

  float         shiftOptimal(fftw_real                      ** ccor_seis_cpp_r,
                             const std::vector<float>        & wellWeight,
                             const std::vector<float>        & dz,
                             int                               nWells,
                             int                               nzp,
                             std::vector<float>              & shiftWell,
                             float                             maxShift);

  void          multiplyPapolouis(fftw_real                 ** vec, 
                                  const std::vector<float>   & dz,
                                  int                          nWells,
                                  int                          nzp, 
                                  float                        waveletLength, 
                                  const std::vector<float>   & wellWeight)    const;

  void          getWavelet(fftw_real                        ** ccor_seis_cpp_r,
                           fftw_real                        ** cor_cpp_r,
                           fftw_real                        ** wavelet_r,
                           const std::vector<float>          & wellWeight,
                           int                                 nWells,
                           int                                 nt);

  void           shiftReal(float                               shift, 
                           fftw_real                         * rAmp,
                           int                                 nt);

  void           convolve(fftw_complex                       * var1_c,
                          fftw_complex                       * var2_c, 
                          fftw_complex                       * out_c,
                          int                                  cnzp)           const;

  void           writeDebugInfo(fftw_real                   ** seis_r,
                                fftw_real                   ** cor_cpp_r,
                                fftw_real                   ** ccor_seis_cpp_r,
                                fftw_real                   ** cpp_r,
                                int                            nWells) const;
};

#endif
