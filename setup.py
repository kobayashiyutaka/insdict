from setuptools import setup, Extension

def main():
    setup(name="insdict",
          version="0.1.0",
          description="Module: Inspect dict.",
          author="Yutaka Kobayashi",
          author_email="kobayashi.yutaka@kochi-tech.ac.jp",
          ext_modules=[Extension("insdict",["insdictmodule.c"])]
          )

if __name__ == "__main__":
    main()



    
          
