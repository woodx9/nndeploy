
#include "nndeploy/model/preprocess/cvtcolor_resize.h"

namespace nndeploy {
namespace model {

base::Status CvtColrResize::run() {
  CvtclorResizeParam* tmp_param =
      dynamic_cast<CvtclorResizeParam*>(param_.get());
  cv::Mat* src = inputs_[0]->getCvMat();
  device::Tensor* dst = outputs_[0]->getTensor();

  int c = dst->getChannel();
  int h = dst->getHeight();
  int w = dst->getWidth();

  cv::Mat tmp = *src;

  if (tmp_param->src_pixel_type_ != tmp_param->dst_pixel_type_) {
    base::CvtColorType cvt_type = base::calCvtColorType(
        tmp_param->src_pixel_type_, tmp_param->dst_pixel_type_);
    if (cvt_type == base::kCvtColorTypeNotSupport) {
      NNDEPLOY_LOGE("cvtColor type not support");
      return base::kStatusCodeErrorNotSupport;
    }
    int cv_cvt_type = OpenCvConvert::convertFromCvtColorType(cvt_type);
    cv::cvtColor(tmp, tmp, cv_cvt_type);
  }

  if (tmp_param->interp_type_ != base::kInterpTypeNotSupport) {
    int interp_type =
        OpenCvConvert::convertFromInterpType(tmp_param->interp_type_);
    cv::resize(*src, tmp, cv::Size(w, h), 0.0, 0.0, interp_type);
  }

  OpenCvConvert::convertToTensor(tmp, dst, tmp_param->scale_, tmp_param->mean_,
                                 tmp_param->std_);

  return base::kStatusCodeOk;
}

}  // namespace model
}  // namespace nndeploy
