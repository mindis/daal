/* file: maximum_pooling1d_layer_forward_types.h */
/*******************************************************************************
* Copyright 2014-2016 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Implementation of forward maximum 1D pooling layer.
//--
*/

#ifndef __MAXIMUM_POOLING1D_LAYER_FORWARD_TYPES_H__
#define __MAXIMUM_POOLING1D_LAYER_FORWARD_TYPES_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "data_management/data/homogen_tensor.h"
#include "data_management/data/homogen_numeric_table.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/pooling1d/maximum_pooling1d_layer_types.h"
#include "algorithms/neural_networks/layers/pooling1d/pooling1d_layer_forward_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace maximum_pooling1d
{
/**
 * @defgroup maximum_pooling1d_forward Forward One-dimensional Max Pooling Layer
 * \copydoc daal::algorithms::neural_networks::layers::maximum_pooling1d::forward
 * @ingroup maximum_pooling1d
 * @{
 */
/**
 * \brief Contains classes for forward maximum 1D pooling layer
 */
namespace forward
{
/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__MAXIMUM_POOLING1D__FORWARD__INPUT"></a>
 * \brief %Input objects for the forward maximum 1D pooling layer
 * See \ref pooling1d::forward::interface1::Input "pooling1d::forward::Input"
 */
class Input : public pooling1d::forward::Input
{};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__MAXIMUM_POOLING1D__FORWARD__RESULT"></a>
 * \brief Provides methods to access the result obtained with the compute() method
 *        of the forward maximum 1D pooling layer
 */
class Result : public pooling1d::forward::Result
{
public:
    /** Default constructor */
    Result() {}
    virtual ~Result() {}

    /**
     * Returns the result of the forward maximum 1D pooling layer
     */
    using layers::forward::Result::get;

    /**
     * Sets the result of the forward maximum 1D pooling layer
     */
    using layers::forward::Result::set;

    /**
     * Allocates memory to store the result of the forward maximum 1D pooling layer
     * \param[in] input Pointer to an object containing the input data
     * \param[in] parameter %Parameter of the forward maximum 1D pooling layer
     * \param[in] method Computation method for the layer
     */
    template <typename algorithmFPType>
    void allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method)
    {
        pooling1d::forward::Result::allocate<algorithmFPType>(input, parameter, method);

        const Parameter *algParameter = static_cast<const Parameter *>(parameter);
        if(!algParameter->predictionStage)
        {
            const Input *in = static_cast<const Input *>(input);

            const services::Collection<size_t> &dataDims = in->get(layers::forward::data)->getDimensions();
            services::Collection<size_t> valueDims(dataDims);
            computeValueDimensions(valueDims, algParameter);

            set(auxSelectedIndices, data_management::TensorPtr(
                    new data_management::HomogenTensor<int>(valueDims, data_management::Tensor::doAllocate)));
            set(auxInputDimensions, createAuxInputDimensions(dataDims));
        }

    }

    /**
     * Returns the result of the forward maximum 1D pooling layer
     * \param[in] id    Identifier of the result
     * \return          Result that corresponds to the given identifier
     */
    data_management::TensorPtr get(LayerDataId id) const
    {
        services::SharedPtr<layers::LayerData> layerData = get(layers::forward::resultForBackward);
        return services::staticPointerCast<data_management::Tensor, data_management::SerializationIface>((*layerData)[id]);
    }

    /**
     * Returns the result of the forward maximum 1D pooling layer
     * \param[in] id    Identifier of the result
     * \return          Result that corresponds to the given identifier
     */
    data_management::NumericTablePtr get(LayerDataNumericTableId id) const
    {
        services::SharedPtr<layers::LayerData> layerData = get(layers::forward::resultForBackward);
        return services::staticPointerCast<data_management::NumericTable, data_management::SerializationIface>((*layerData)[id]);
    }

    /**
     * Sets the result of the forward maximum 1D pooling layer
     * \param[in] id Identifier of the result
     * \param[in] ptr Result
     */
    void set(LayerDataId id, const data_management::TensorPtr &ptr)
    {
        services::SharedPtr<layers::LayerData> layerData = get(layers::forward::resultForBackward);
        (*layerData)[id] = ptr;
    }

    /**
     * Sets the result of the forward maximum 1D pooling layer
     * \param[in] id Identifier of the result
     * \param[in] ptr Result
     */
    void set(LayerDataNumericTableId id, const data_management::NumericTablePtr &ptr)
    {
        services::SharedPtr<layers::LayerData> layerData = get(layers::forward::resultForBackward);
        (*layerData)[id] = ptr;
    }

    /**
     * Checks the result of the forward maximum 1D pooling layer
     * \param[in] input     %Input of the layer
     * \param[in] parameter %Parameter of the layer
     * \param[in] method    Computation method of the layer
     */
    void check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, int method) const DAAL_C11_OVERRIDE
    {
        pooling1d::forward::Result::check(input, parameter, method);
    }

    /**
     * Returns the serialization tag of the forward maximum 1D pooling layer result
     * \return     Serialization tag of the forward maximum 1D pooling layer result
     */
    int getSerializationTag() DAAL_C11_OVERRIDE  { return SERIALIZATION_NEURAL_NETWORKS_LAYERS_MAXIMUM_POOLING1D_FORWARD_RESULT_ID; }

    /**
     * Serializes the object
     * \param[in]  arch  Storage for the serialized object or data structure
     */
    void serializeImpl(data_management::InputDataArchive  *arch) DAAL_C11_OVERRIDE
    {serialImpl<data_management::InputDataArchive, false>(arch);}

    /**
     * Deserializes the object
     * \param[in]  arch  Storage for the deserialized object or data structure
     */
    void deserializeImpl(data_management::OutputDataArchive *arch) DAAL_C11_OVERRIDE
    {serialImpl<data_management::OutputDataArchive, true>(arch);}

protected:
    /** \private */
    template<typename Archive, bool onDeserialize>
    void serialImpl(Archive *arch)
    {
        daal::algorithms::Result::serialImpl<Archive, onDeserialize>(arch);
    }
};

} // namespace interface1
using interface1::Input;
using interface1::Result;

} // namespace forward
/** @} */
} // namespace maximum_pooling1d
} // namespace layers
} // namespace neural_networks
} // namespace algorithm
} // namespace daal

#endif
