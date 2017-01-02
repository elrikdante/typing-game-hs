{-# LANGUAGE ForeignFunctionInterface #-}

import Foreign
import Foreign.Ptr
import Foreign.C.Types
import Foreign.C.String
import Foreign.Marshal.Alloc
import Foreign.C.String

import Control.Monad
import Control.Concurrent
foreign import ccall unsafe "lib.h some_func" 
  some_func :: CInt -> CInt -> CInt

foreign import ccall safe "lib.h some_func_impure"
  some_func':: CInt -> CInt -> IO CInt

foreign import ccall safe "lib.h setup"
  sdlSetup :: IO ()

foreign import ccall unsafe "lib.h alert"
  sdlAlert :: Ptr CChar -> IO ()

foreign import ccall unsafe "lib.h loop"
  sdlRunFrame :: IO ()

main = do
     sdlSetup
     withCAString "Some Words" $ \cstr -> do
       str <- peekCAString cstr
       print $ "The Str: " ++ str
       sdlAlert cstr
     forM_ (repeat (undefined :: Int)) $ \_ -> do
        sdlRunFrame


