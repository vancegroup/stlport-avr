// This file is reserved to site configuration purpose
// and should NEVER be overridden by user

# if defined ( __STL_NO_SGI_IOSTREAMS )

// User choose not to use SGI iostreams, which means no
// precompiled library will be used and he is free to override
// any STLport configuration flags

# else

// The following will be defined in stl_config.h :
// # define __SGI_STL_OWN_IOSTREAMS 1
# endif

