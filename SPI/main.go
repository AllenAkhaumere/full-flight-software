package main

import (
	"fmt"
	"gopkg.in/yaml.v2"
	"io/ioutil"
	"path/filepath"
	"strconv"
	spi "golang.org/x/exp/io/spi"
  )

var devlist []*spi.Device
func loadConfig() {
	filename, _ := filepath.Abs("config_default.yml")
	yamlFile, err := ioutil.ReadFile(filename)
  
	if err != nil {
	  panic(err)
	}
  
	var config Config

	err = yaml.Unmarshal(yamlFile, &config)
	if err != nil {
	  panic(err)
	}
	fmt.Printf("%#v\n", config)	
	fmt.Printf("Value: %#v\n", config.Sensors)
	for _, element:= range config.Sensors{
		fmt.Println(element[0]+element[1]+element[2])
		//openSensor(element[0]+element[1]+element[2])
	}
}
type Config struct{
	Sensors map[string][]string
}

func openSensor(a, b, c string){
	newc, _ := strconv.Atoi(c)
	newb, _ := strconv.Atoi(b)
	dev, err := spi.Open(&spi.Devfs{
					Dev:      a,
					Mode:     spi.Mode(newb),
					MaxSpeed: int64(newc),
	})
	if err != nil {
					panic(err)
	}
	devlist = append(devlist, dev)
}

func main(){
	loadConfig()
}