// Masten SG's C standard base.

// Preprocessor macro definitions  ///////////////////////////////////////////

#define sign(x) ((x) == 0 ? 0 : ((x) < 0 ? -1 : 1))

// please() is a milder assert()
// TODO: only enable when debugging
#define please(x)                                             \
  if (!(x)) {                                                 \
    fprintf(stderr, "%s:%d !(" #x ")\n", __FILE__, __LINE__); \
  }

#define would_be_nice_if please

// Type definitions  /////////////////////////////////////////////////////////

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef size_t usize;
typedef ssize_t isize;
typedef float f32;
typedef double f64;

// Function definitions  /////////////////////////////////////////////////////
