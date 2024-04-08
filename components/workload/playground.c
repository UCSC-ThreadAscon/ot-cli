#include "workload.h"

void CoapSecure::HandleRequest(otMessage *aMessage, const otMessageInfo *aMessageInfo)
{
    otError    error           = OT_ERROR_NONE;
    otMessage *responseMessage = nullptr;
    otCoapCode responseCode    = OT_COAP_CODE_EMPTY;

    OutputFormat("coaps request from ");
    OutputIp6Address(aMessageInfo->mPeerAddr);
    OutputFormat(" ");

    switch (otCoapMessageGetCode(aMessage))
    {
    case OT_COAP_CODE_GET:
        OutputFormat("GET");
        break;

    case OT_COAP_CODE_DELETE:
        OutputFormat("DELETE");
        break;

    case OT_COAP_CODE_PUT:
        OutputFormat("PUT");
        break;

    case OT_COAP_CODE_POST:
        OutputFormat("POST");
        break;

    default:
        OutputLine("Undefined");
    }

    PrintPayload(aMessage);

    if ((otCoapMessageGetType(aMessage) == OT_COAP_TYPE_CONFIRMABLE) ||
        (otCoapMessageGetCode(aMessage) == OT_COAP_CODE_GET))
    {
        if (otCoapMessageGetCode(aMessage) == OT_COAP_CODE_GET)
        {
            responseCode = OT_COAP_CODE_CONTENT;
        }
        else
        {
            responseCode = OT_COAP_CODE_VALID;
        }

        responseMessage = otCoapNewMessage(GetInstancePtr(), nullptr);
        VerifyOrExit(responseMessage != nullptr, error = OT_ERROR_NO_BUFS);

        SuccessOrExit(
            error = otCoapMessageInitResponse(responseMessage, aMessage, OT_COAP_TYPE_ACKNOWLEDGMENT, responseCode));

        if (otCoapMessageGetCode(aMessage) == OT_COAP_CODE_GET)
        {
            SuccessOrExit(error = otCoapMessageSetPayloadMarker(responseMessage));
                SuccessOrExit(error = otMessageAppend(responseMessage, &mResourceContent,
                                                      static_cast<uint16_t>(strlen(mResourceContent))));
        }

            SuccessOrExit(error = otCoapSecureSendResponse(GetInstancePtr(), responseMessage, aMessageInfo));
    }

exit:

    if (error != OT_ERROR_NONE)
    {
        if (responseMessage != nullptr)
        {
            OutputLine("coaps send response error %d: %s", error, otThreadErrorToString(error));
            otMessageFree(responseMessage);
        }
    }
    else if (responseCode >= OT_COAP_CODE_RESPONSE_MIN)
    {
        OutputLine("coaps response sent");
    }
}