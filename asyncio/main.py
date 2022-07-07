#!/usr/bin/env python3
 
import asyncio 
import threading
import os 
 
  
    
async def run():
    current_dir = os.getcwd()
    x = threading.Thread(target=os.system  , args=(f"{current_dir}/sleeping.exe",))
    x.start()
    x.join()
    return 12
     
async def main():
    task = asyncio.create_task(run())
    awitable = asyncio.wait({task})
    ret = await awitable
    print(ret)
    

if __name__ == "__main__":
    asyncio.run(main())


 