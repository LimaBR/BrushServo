/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.5 */

#ifndef PB_OUTPUT_PB_H_INCLUDED
#define PB_OUTPUT_PB_H_INCLUDED
#include "pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct _OmegaOutput { 
    float omega; /* Velocidade do motor em rad/s */
    float current; /* Corrente em Amperes */
} OmegaOutput;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define OmegaOutput_init_default                 {0, 0}
#define OmegaOutput_init_zero                    {0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define OmegaOutput_omega_tag                    1
#define OmegaOutput_current_tag                  2

/* Struct field encoding specification for nanopb */
#define OmegaOutput_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    omega,             1) \
X(a, STATIC,   SINGULAR, FLOAT,    current,           2)
#define OmegaOutput_CALLBACK NULL
#define OmegaOutput_DEFAULT NULL

extern const pb_msgdesc_t OmegaOutput_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define OmegaOutput_fields &OmegaOutput_msg

/* Maximum encoded size of messages (where known) */
#define OmegaOutput_size                         10

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif