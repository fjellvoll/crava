/***************************************************************************
*      Copyright (C) 2008 by Norwegian Computing Center and Statoil        *
***************************************************************************/

#ifndef MODELAVODYNAMIC_H
#define MODELAVODYNAMIC_H

#include <stdio.h>

#include "nrlib/surface/regularsurface.hpp"

#include "src/vario.h"
#include "src/definitions.h"
//#include "src/background.h" //or move getAlpha & co to cpp-file.
#include "src/modelsettings.h"
#include "src/inputfiles.h"
#include "src/commondata.h"

struct irapgrid;
class Wavelet;
class Wavelet1D;
class Simbox;
class FFTGrid;
class RandomGen;
class GridMapping;
class InputFiles;
class ModelAVOStatic;
class ModelGeneral;
class SeismicParametersHolder;
//class CommonData;

class ModelAVODynamic
{
public:
  //ModelAVODynamic(ModelSettings               *& modelSettings,
  //                const InputFiles             * inputFiles,
  //                std::vector<bool>              failedGeneralDetails,
  //                std::vector<bool>              failedStaticDetails,
  //                const Simbox                 * timeSimbox,
  //                const Simbox                 * timeBGSimbox,
  //                const Surface                * correlationDirection,
  //                RandomGen                    * /*randomGen*/,
  //                GridMapping                  * timeDepthMapping,
  //                const GridMapping            * timeCutMapping,
  //                const std::vector<Surface *> & waveletEstimInterval,
  //                const std::vector<Surface *> & /*wellMoveInterval*/,
  //                const std::vector<Surface *> & /*faciesEstimInterval*/,
  //                ModelAVOStatic               * modelAVOstatic,
  //                ModelGeneral                 * modelGeneral,
  //                int                            t,
  //                SeismicParametersHolder      & seismicParameters);    // modelAVOstatic::wells_ are altered. modelAVOstatic is deliberately sent in as un-const.

  //ModelAVODynamic(ModelSettings          *& modelSettings,
  //                const InputFiles        * inputFiles,
  //                ModelAVOStatic          * modelAVOstatic,
  //                ModelGeneral            * modelGeneral,
  //                SeismicParametersHolder & seismicParameters,
  //                const Simbox            * timeSimbox,
  //                const Surface           * correlationDirection,
  //                const GridMapping       * timeDepthMapping,
  //                const GridMapping       * timeCutMapping,
  //                int                       t);

  ModelAVODynamic(ModelSettings          *& model_settings,
                  ModelAVOStatic          * model_avo_static,
                  ModelGeneral            * model_general,
                  CommonData              * common_data,
                  SeismicParametersHolder & seismic_parameters,
                  const Simbox            * simbox,
                  int                       t,
                  int                       i_interval);

  //ModelAVODynamic(ModelSettings               *& modelSettings,
  //                const InputFiles             * inputFiles,
  //                //std::vector<bool>              failedGeneralDetails,
  //                //std::vector<bool>              failedStaticDetails,
  //                const Simbox                 * timeSimbox,
  //                //const Simbox                 * timeBGSimbox,
  //                //const Surface                * correlationDirection,
  //                RandomGen                    * /*randomGen*/,
  //                GridMapping                  * timeDepthMapping,
  //                //const GridMapping            * timeCutMapping,
  //                const std::vector<Surface *> & waveletEstimInterval,
  //                const std::vector<Surface *> & /*wellMoveInterval*/,
  //                const std::vector<Surface *> & /*faciesEstimInterval*/,
  //                ModelAVOStatic               * modelAVOstatic,
  //                ModelGeneral                 * modelGeneral,
  //                CommonData                   * commonData,
  //                int                            t,
  //                SeismicParametersHolder      & seismicParameters,
  //                int                            i_interval);

  //ModelAVODynamic(ModelSettings          *& modelSettings,
  //                const InputFiles        * inputFiles,
  //                ModelAVOStatic          * modelAVOstatic,
  //                ModelGeneral            * modelGeneral,
  //                CommonData              * commoData,
  //                SeismicParametersHolder & seismicParameters,
  //                const Simbox            * timeSimbox,
  //                //const Surface           * correlationDirection,
  //                const GridMapping       * timeDepthMapping,
  //                //const GridMapping       * timeCutMapping,
  //                int                       t,
  //                int                       i_interval);

  ~ModelAVODynamic();

  //FFTGrid                    ** getSeisCubes()             const { return seisCube_               ;}
  //Wavelet                    ** getWavelets()              const { return wavelet_                ;}
  std::vector<FFTGrid *>        GetSeisCubes()             const { return seis_cubes_                     ;}
  std::vector<Wavelet *>        GetWavelets()              const { return wavelets_                       ;}

  float                      ** GetAMatrix()               const { return reflection_matrix_              ;}
  Grid2D                      * GetLocalNoiseScale(int i)  const { return local_noise_scale_[i]           ;}
  const std::vector<Grid2D *> & GetLocalNoiseScales()      const { return local_noise_scale_              ;}

  bool                          GetFailed()                const { return failed_                         ;}
  //std::vector<bool>             getFailedDetails()         const { return failed_details_         ;}

  const std::vector<std::vector<float> > & GetAngularCorr() const { return angular_corr_                  ;}

  float                         GetSNRatioAngle(int i)     const { return sn_ratio_[i]                    ;}
  std::vector<float>            GetSNRatio()               const { return sn_ratio_                       ;}
  bool                          GetUseLocalNoise()         const { return use_local_noise_                ;}
  float                         GetAngle(int i)            const { return angle_[i]                       ;}
  //bool                          getEstimateWavelet(int i)  const { return estimateWavelet_[i]             ;}
  //bool                          getMatchEnergies(int i)    const { return matchEnergies_[i]               ;}
  int                           GetNumberOfAngles()        const { return static_cast<int>(angle_.size()) ;}

  float                       * GetThetaDeg()              const { return theta_deg_                      ;}
  float                       * GetDataVariance()          const { return data_variance_                  ;}
  float                       * GetErrorVariance()         const { return error_variance_                 ;}
  float                       * GetModelVariance()         const { return model_variance_                 ;}
  float                       * GetSignalVariance()        const { return signal_variance_                ;}
  float                       * GetTheoSNRatio()           const { return theo_sn_ratio_                  ;}
  double                     ** GetErrThetaCov()           const { return err_theta_cov_                  ;}

  void                          ReleaseGrids();                        // Cuts connection to SeisCube_

  //static float  ** readMatrix(const std::string & fileName,
  //                            int                 n1,
  //                            int                 n2,
  //                            const std::string & readReason,
  //                            std::string       & errText);

  //static void             processBackground(Background                    *& background,
  //                                          const std::vector<WellData *>  & wells,
  //                                          const Simbox                   * timeSimbox,
  //                                          const Simbox                   * timeBGSimbox,
  //                                          GridMapping                   *& timeDepthMapping,
  //                                          const GridMapping              * timeCutMapping,
  //                                          const ModelSettings            * modelSettings,
  //                                          ModelGeneral                   * modelGeneral,
  //                                          const InputFiles               * inputFile,
  //                                          const int                      & thisTimeLapse,
  //                                          std::string                    & errText,
  //                                          bool                           & failed);
private:
  //void             ProcessSeismic(FFTGrid         **& seisCube,
  //                                const Simbox      * timeSimbox,
  //                                const GridMapping * timeDepthMapping,
  //                                const GridMapping * timeCutMapping,
  //                                const ModelSettings * modelSettings,
  //                                const InputFiles  * inputFiles,
  //                                std::string       & errText,
  //                                bool              & failed);


  //void             processReflectionMatrix(float               **& reflectionMatrix,
  //                                         const Background      * background,
  //                                         const std::vector<WellData *> & wells,
  //                                         const ModelSettings   * modelSettings,
  //                                         const InputFiles      * inputFiles,
  //                                         std::string           & errText,
  //                                         bool                  & failed);

  //void             processWavelets(Wavelet                    **& wavelet,
  //                                 FFTGrid                     ** seisCube,
  //                                 std::vector<WellData *>        wells,
  //                                 const float          * const * reflectionMatrix,
  //                                 const Simbox                 * timeSimbox,
  //                                 const Surface                * correlationDirection,
  //                                 const std::vector<Surface *> & waveletEstimInterval,
  //                                 ModelSettings                * modelSettings,
  //                                 const InputFiles             * inputFiles,
  //                                 std::string                  & errText,
  //                                 bool                         & failed);

  //int              process1DWavelet(const ModelSettings          * modelSettings,
  //                                  const InputFiles             * inputFiles,
  //                                  const Simbox                 * timeSimbox,
  //                                  //const FFTGrid        * const * seisCube,
  //                                  std::vector<WellData *>        wells,
  //                                  //const std::vector<Surface *> & waveletEstimInterval,
  //                                  const float                  * reflectionMatrix,
  //                                  std::string                  & errText,
  //                                  Wavelet                     *& wavelet,
  //                                  unsigned int                   i,
  //                                  bool                           useRickerWavelet);

 //int               process3DWavelet(const ModelSettings                     * modelSettings,
 //                                   const InputFiles                        * inputFiles,
 //                                   const Simbox                            * timeSimbox,
 //                                   //const FFTGrid                   * const * seisCube,
 //                                   //const std::vector<WellData *>           & wells,
 //                                   //const std::vector<Surface *>            & waveletEstimInterval,
 //                                   const float                             * reflectionMatrix,
 //                                   std::string                             & errText,
 //                                   Wavelet                                *& wavelet,
 //                                   unsigned int                              i);

  //void             setupDefaultReflectionMatrix(float       **& reflectionMatrix,
  //                                              double          vsvp,
  //                                              const ModelSettings * modelSettings);
  //int              getWaveletFileFormat(const std::string & fileName,
  //                                      std::string & errText);
  //double           vsvpFromWells(const std::vector<WellData *> & wells,
  //                               int                     nWells);

  void             VsVpFromWells(CommonData * common_data,
                                 int          i_interval,
                                 double     & vsvp,
                                 int        & N);

  void             FindMeanVsVp(const NRLib::Well            & well,
                                const NRLib::Surface<double> & top,
                                const NRLib::Surface<double> & bot,
                                double                       & mean_vs_vp,
                                int                          & n_vs_vp);

  //void             readAndWriteLocalGridsToFile(const std::string   & fileName,
  //                                              const std::string   & type,
  //                                              const float           scaleFactor,
  //                                              const ModelSettings * modelSettings,
  //                                              const unsigned int    i,
  //                                              const Simbox        * timeSimbox,
  //                                              const Grid2D        * grid);
  //void             resampleSurfaceToGrid2D(const Simbox  * simbox,
  //                                         const Surface * surface,
  //                                         Grid2D        * outgrid);
  //void             resampleGrid2DToSurface(const Simbox  * simbox,
  //                                         const Grid2D  * grid,
  //                                         Surface      *& surface);

  bool             FindTimeGradientSurface(const std::string     & refTimeFile,
                                           const Simbox          * simbox,
                                           NRLib::Grid2D<float>  & refTimeGradX,
                                           NRLib::Grid2D<float>  & refTimeGradY);

  //void             computeStructureDepthGradient(double                 v0,
  //                                               double                 radius,
  //                                               const Simbox         * timeSimbox,
  //                                               const Surface        * t0Surf,
  //                                               const Surface        * correlationDirection,
  //                                               NRLib::Grid2D<float> & structureDepthGradX,
  //                                               NRLib::Grid2D<float> & structureDepthGradY);
  //void            computeReferenceTimeGradient(const Simbox         * timeSimbox,
  //                                             const Surface        * t0Surf,
  //                                             NRLib::Grid2D<float> & refTimeGradX,
  //                                             NRLib::Grid2D<float> & refTimeGradY);

  //void              calculateSmoothGrad(const Surface * surf, double x, double y, double radius, double ds,  double& gx, double& gy);

  void              ComputeDataVariance(std::vector<FFTGrid *> & seisData,
                                        float                  * dataVariance,
                                        int                      nx,
                                        int                      ny,
                                        int                      nz,
                                        int                      nxp,
                                        int                      nyp,
                                        int                      nzp);

  void              SetupErrorCorrelation(const std::vector<Grid2D *> & noiseScale,
                                          const float                 * dataVariance,
                                          float                       * errorVariance,
                                          double                     ** errThetaCov);

  float             ComputeWDCorrMVar(Wavelet1D* WD,
                                      fftw_real* corrT,
                                      int        nzp);

  int                       number_of_angles_;

  std::vector<Wavelet *>    wavelets_;               ///< Wavelet for angle
  std::vector<FFTGrid *>    seis_cubes_;             ///< Seismic data cubes

  float                  ** reflection_matrix_;      ///< May specify own Zoeppritz-approximation. Default NULL,
                                                     ///< indicating that standard approximation will be used.

  GridMapping             * time_depth_mapping_;      ///< Contains both simbox and mapping used for depth conversion
  //GridMapping             * timeCutMapping_;        ///< Simbox and mapping for timeCut*/

  std::vector<Grid2D *>     local_noise_scale_;       ///< Scale factors for local noise

  bool                      failed_;                  ///< Indicates whether errors occured during construction.
  //std::vector<bool>         failed_details_;        ///< Detailed failed information.

  std::vector<std::vector<float > > angular_corr_;    ///< correlations between angle i and j.

  std::vector<float>        sn_ratio_;
  std::vector<float>        angle_;
  //std::vector<bool>         matchEnergies_;
  //std::vector<bool>         estimateWavelet_;
  bool                      use_local_noise_;
  int                       this_timelapse_;

  float                   * theta_deg_;
  float                   * data_variance_;
  float                   * error_variance_;
  float                   * model_variance_;
  float                   * signal_variance_;
  float                   * theo_sn_ratio_;      // signal noise ratio from model

  double                 ** err_theta_cov_;

};

#endif
