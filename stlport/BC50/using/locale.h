// from <cwchar>
#if !defined (__STL_NO_MBSTATE_T)
using __STL_VENDOR_MB_NAMESPACE::mbstate_t;
#endif

// _lib.locale_, locale:
using __STL_NEW_IO_NAMESPACE::locale;
using __STL_NEW_IO_NAMESPACE::use_facet;
using __STL_NEW_IO_NAMESPACE::has_facet;

// _lib.locale.convenience_, convenience interfaces:
using __STL_NEW_IO_NAMESPACE::isspace;
using __STL_NEW_IO_NAMESPACE::isprint;
using __STL_NEW_IO_NAMESPACE::iscntrl;
using __STL_NEW_IO_NAMESPACE::isupper;
using __STL_NEW_IO_NAMESPACE::islower;
using __STL_NEW_IO_NAMESPACE::isalpha;
using __STL_NEW_IO_NAMESPACE::isdigit;
using __STL_NEW_IO_NAMESPACE::ispunct;
using __STL_NEW_IO_NAMESPACE::isxdigit;
using __STL_NEW_IO_NAMESPACE::isalnum;
using __STL_NEW_IO_NAMESPACE::isgraph;
using __STL_NEW_IO_NAMESPACE::toupper;
using __STL_NEW_IO_NAMESPACE::tolower;

// _lib.category.ctype_ and _lib.facet.ctype.special_, ctype:
using __STL_NEW_IO_NAMESPACE::ctype_base;
using __STL_NEW_IO_NAMESPACE::ctype;
using __STL_NEW_IO_NAMESPACE::ctype_byname;
using __STL_NEW_IO_NAMESPACE::codecvt_base;
using __STL_NEW_IO_NAMESPACE::codecvt;
using __STL_NEW_IO_NAMESPACE::codecvt_byname;

// _lib.category.numeric_ and _lib.facet.numpunct_, numeric:
using __STL_NEW_IO_NAMESPACE::num_get;
using __STL_NEW_IO_NAMESPACE::num_put;
using __STL_NEW_IO_NAMESPACE::numpunct;
using __STL_NEW_IO_NAMESPACE::numpunct_byname;

// _lib.category.collate_, collation:
using __STL_NEW_IO_NAMESPACE::collate;
using __STL_NEW_IO_NAMESPACE::collate_byname;

// _lib.category.time_, date and time:
using __STL_NEW_IO_NAMESPACE::time_base;
using __STL_NEW_IO_NAMESPACE::time_get;
using __STL_NEW_IO_NAMESPACE::time_get_byname;
using __STL_NEW_IO_NAMESPACE::time_put;
using __STL_NEW_IO_NAMESPACE::time_put_byname;

// _lib.category.monetary_, money:
using __STL_NEW_IO_NAMESPACE::money_base;
using __STL_NEW_IO_NAMESPACE::money_get;
using __STL_NEW_IO_NAMESPACE::money_put;
using __STL_NEW_IO_NAMESPACE::moneypunct;
using __STL_NEW_IO_NAMESPACE::moneypunct_byname;

#if !defined (__SGI_STL_OWN_IOSTREAMS) && !defined (__STL_NO_NATIVE_MESSAGE_FACET)
using __STL_NEW_IO_NAMESPACE::messages_base;
using __STL_NEW_IO_NAMESPACE::messages;
using __STL_NEW_IO_NAMESPACE::messages_byname;
#endif // _MSL_NO_MESSAGE_FACET
