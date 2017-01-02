{-# LANGUAGE ForeignFunctionInterface #-}

import Foreign
import Foreign.Ptr
import Foreign.C.Types
import Foreign.C.String
import Control.Monad
import Control.Concurrent
foreign import ccall unsafe "lib.h some_func" 
  some_func :: CInt -> CInt -> CInt

foreign import ccall safe "lib.h some_func_impure"
  some_func':: CInt -> CInt -> IO CInt

foreign import ccall safe "lib.h setup"
  sdlSetup :: IO ()

main = do
     print "Hello"
     print (show $ some_func 30 30)
     print (show $ some_func 40 30)
     some_func' 10 30
     some_func' 12 30
     sdlSetup
     forM_ (repeat (undefined :: Int)) $ \_ -> do
       threadDelay 60000000
       print "Hello"
     	  


