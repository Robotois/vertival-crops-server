{
  "targets": [
    {
      "target_name": "IOModule",
      "sources": [ "src/Wrapper/IOModule.cpp","src/Wrapper/IOModuleWrapper.cpp",
      "src/Modules/IOModule.cpp",
      "src/Libraries/MCP23008/MCP23008.cpp"
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
