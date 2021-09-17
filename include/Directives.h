//
// Created by Gautam Sharma on 9/12/21.
//

#ifndef UNTITLED_DIRECTIVES_H
#define UNTITLED_DIRECTIVES_H
# include <vector>
/*
 * Some syntactic sugar :)
 */


#define  __NO_DISCARD__ [[nodiscard]]
#define __ASSERT__  assert
#define __STATIC_ASSERT__  static_assert
#define __LIKELY__ [[likely]]
#define __UNLIKELY__ [[unlikely]]
#define TW TensorWrapper
#define __DO_NOT_CALL__ // Not intended to be called by any client
#define __ONLY_FOR_TESTING__ // Function only defined for testing. Do not use !
#define __INTERNAL__ // only for internal use
#define __PUBLIC__ // Intended to be used by clients



#endif //DIRECTIVES_H
