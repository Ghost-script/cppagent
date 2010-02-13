/*
* Copyright (c) 2008, AMT – The Association For Manufacturing Technology (“AMT”)
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of the AMT nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* DISCLAIMER OF WARRANTY. ALL MTCONNECT MATERIALS AND SPECIFICATIONS PROVIDED
* BY AMT, MTCONNECT OR ANY PARTICIPANT TO YOU OR ANY PARTY ARE PROVIDED "AS IS"
* AND WITHOUT ANY WARRANTY OF ANY KIND. AMT, MTCONNECT, AND EACH OF THEIR
* RESPECTIVE MEMBERS, OFFICERS, DIRECTORS, AFFILIATES, SPONSORS, AND AGENTS
* (COLLECTIVELY, THE "AMT PARTIES") AND PARTICIPANTS MAKE NO REPRESENTATION OR
* WARRANTY OF ANY KIND WHATSOEVER RELATING TO THESE MATERIALS, INCLUDING, WITHOUT
* LIMITATION, ANY EXPRESS OR IMPLIED WARRANTY OF NONINFRINGEMENT,
* MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. 

* LIMITATION OF LIABILITY. IN NO EVENT SHALL AMT, MTCONNECT, ANY OTHER AMT
* PARTY, OR ANY PARTICIPANT BE LIABLE FOR THE COST OF PROCURING SUBSTITUTE GOODS
* OR SERVICES, LOST PROFITS, LOSS OF USE, LOSS OF DATA OR ANY INCIDENTAL,
* CONSEQUENTIAL, INDIRECT, SPECIAL OR PUNITIVE DAMAGES OR OTHER DIRECT DAMAGES,
* WHETHER UNDER CONTRACT, TORT, WARRANTY OR OTHERWISE, ARISING IN ANY WAY OUT OF
* THIS AGREEMENT, USE OR INABILITY TO USE MTCONNECT MATERIALS, WHETHER OR NOT
* SUCH PARTY HAD ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.
*/

#include "xml_printer_test.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(XmlPrinterTest);

using namespace std;

void XmlPrinterTest::setUp()
{
  config = new XmlParser("../samples/test_config.xml");
  devices = config->getDevices();
}

void XmlPrinterTest::tearDown()
{
  delete config;
}

void XmlPrinterTest::testInitXmlDoc()
{
  // Devices
  xmlpp::Document *initXml1 =
    XmlPrinter::initXmlDoc("Devices", 12345, 100000, 10);
  
  // Root
  xmlpp::Element *root1 = initXml1->get_root_node();
  CPPUNIT_ASSERT_EQUAL(
    (Glib::ustring) "urn:mtconnect.org:MTConnectDevices:1.1",
    root1->get_attribute_value("xmlns:m")
  );
  CPPUNIT_ASSERT_EQUAL(
    (Glib::ustring) "http://www.w3.org/2001/XMLSchema-instance",
    root1->get_attribute_value("xmlns:xsi")
  );
  CPPUNIT_ASSERT_EQUAL(
    (Glib::ustring) "urn:mtconnect.org:MTConnectDevices:1.1",
    root1->get_attribute_value("xmlns")
  );
  CPPUNIT_ASSERT_EQUAL(
    (Glib::ustring) "urn:mtconnect.org:MTConnectDevices:1.1"
      + " http://www.mtconnect.org/schemas/MTConnectDevices.xsd",
    root1->get_attribute_value("xsi:schemaLocation")
  );
  
  // Header
  xmlpp::Node::NodeList rootChildren1 = root1->get_children("Header");
  CPPUNIT_ASSERT_EQUAL((size_t) 1, rootChildren1.size());
  
  xmlpp::Element *header1 =
    dynamic_cast<xmlpp::Element *>(rootChildren1.front());
  CPPUNIT_ASSERT(header1);
  
  CPPUNIT_ASSERT_EQUAL((Glib::ustring) "localhost",
    header1->get_attribute_value("sender"));
  CPPUNIT_ASSERT_EQUAL((Glib::ustring) "12345",
    header1->get_attribute_value("instanceId"));
  CPPUNIT_ASSERT_EQUAL((Glib::ustring) "100000",
    header1->get_attribute_value("bufferSize"));
  CPPUNIT_ASSERT_EQUAL((Glib::ustring) "1.1",
    header1->get_attribute_value("version"));
  
  CPPUNIT_ASSERT(header1->get_attribute_value("nextSequence").empty());
  CPPUNIT_ASSERT(header1->get_attribute_value("firstSequence").empty());
  CPPUNIT_ASSERT(header1->get_attribute_value("lastSequence").empty());
  
  // Streams
  xmlpp::Document *initXml2 =
    XmlPrinter::initXmlDoc("Streams", 54321, 100000, 10, 1);
  
  // Root
  xmlpp::Element *root2 = initXml2->get_root_node();
  CPPUNIT_ASSERT_EQUAL(
    (Glib::ustring) "urn:mtconnect.org:MTConnectStreams:1.1",
    root2->get_attribute_value("xmlns:m")
  );
  CPPUNIT_ASSERT_EQUAL(
    (Glib::ustring) "http://www.w3.org/2001/XMLSchema-instance",
    root2->get_attribute_value("xmlns:xsi")
  );
  CPPUNIT_ASSERT_EQUAL(
    (Glib::ustring) "urn:mtconnect.org:MTConnectStreams:1.1",
    root2->get_attribute_value("xmlns")
  );
  CPPUNIT_ASSERT_EQUAL(
    (Glib::ustring) "urn:mtconnect.org:MTConnectStreams:1.1"
      + " http://www.mtconnect.org/schemas/MTConnectStreams.xsd",
    root2->get_attribute_value("xsi:schemaLocation")
  );
  
  // Header
  xmlpp::Node::NodeList rootChildren2 = root2->get_children("Header");
  CPPUNIT_ASSERT_EQUAL((size_t) 1, rootChildren2.size());
  
  xmlpp::Element *header2 =
    dynamic_cast<xmlpp::Element *>(rootChildren2.front());
  CPPUNIT_ASSERT(header2);
  
  CPPUNIT_ASSERT_EQUAL((Glib::ustring) "localhost",
    header2->get_attribute_value("sender"));
  CPPUNIT_ASSERT_EQUAL((Glib::ustring) "54321",
    header2->get_attribute_value("instanceId"));
  CPPUNIT_ASSERT_EQUAL((Glib::ustring) "100000",
    header2->get_attribute_value("bufferSize"));
  CPPUNIT_ASSERT_EQUAL((Glib::ustring) "1.1",
    header2->get_attribute_value("version"));
  
  CPPUNIT_ASSERT_EQUAL((Glib::ustring) "10",
    header2->get_attribute_value("nextSequence"));
  CPPUNIT_ASSERT_EQUAL((Glib::ustring) "1",
    header2->get_attribute_value("firstSequence"));
  CPPUNIT_ASSERT_EQUAL((Glib::ustring) "9",
    header2->get_attribute_value("lastSequence"));
  
  delete initXml1;
  delete initXml2;
}

void XmlPrinterTest::testPrintNode()
{
  xmlpp::Document doc;
  
  xmlpp::Element *root = doc.create_root_node("Root");
  xmlpp::Element *child1 = root->add_child("Child1");
  xmlpp::Element *child2 = root->add_child("Child2");
  xmlpp::Element *grandChild = child2->add_child("GrandChild");
  
  child1->set_attribute("abc", "def");
  child1->set_attribute("ABC", "DEF");
  grandChild->set_child_text("TEXT!!!");
  
  string expected;
  
  expected += "<Root>\n";
  expected += "  <Child1 abc=\"def\" ABC=\"DEF\" />\n";
  expected += "  <Child2>\n";
  expected += "    <GrandChild>TEXT!!!</GrandChild>\n";
  expected += "  </Child2>\n";
  expected += "</Root>\n";
  
  CPPUNIT_ASSERT_EQUAL(expected, XmlPrinter::printNode(root));
}

void XmlPrinterTest::testPrintIndentation()
{
  CPPUNIT_ASSERT(XmlPrinter::printIndentation(0).empty());
  CPPUNIT_ASSERT_EQUAL((string) "  ",
    XmlPrinter::printIndentation(2));
  CPPUNIT_ASSERT_EQUAL((string) "    ",
    XmlPrinter::printIndentation(4));
  CPPUNIT_ASSERT_EQUAL((string) "      ",
    XmlPrinter::printIndentation(6));
  CPPUNIT_ASSERT_EQUAL((string) "        ",
    XmlPrinter::printIndentation(8));
  CPPUNIT_ASSERT_EQUAL((string) "                    ",
    XmlPrinter::printIndentation(20));
}

void XmlPrinterTest::testAddAttributes()
{
  xmlpp::Document doc;
  
  xmlpp::Element *element = doc.create_root_node("Root");
  
  CPPUNIT_ASSERT(element->get_attribute_value("a").empty());
  CPPUNIT_ASSERT(element->get_attribute_value("key1").empty());
  CPPUNIT_ASSERT(element->get_attribute_value("key2").empty());
  
  map<string, string> attributes;
  attributes["a"] = "A";
  attributes["key1"] = "value1";
  attributes["key2"] = "value2";
  
  XmlPrinter::addAttributes(element, &attributes);
  
  CPPUNIT_ASSERT_EQUAL((Glib::ustring) "A", element->get_attribute_value("a"));
  CPPUNIT_ASSERT_EQUAL((Glib::ustring) "value1",
    element->get_attribute_value("key1"));
  CPPUNIT_ASSERT_EQUAL((Glib::ustring) "value2",
    element->get_attribute_value("key2"));
}

void XmlPrinterTest::testGetDeviceStream()
{
  xmlpp::Document doc;
  xmlpp::Element *root = doc.create_root_node("Root");
  
  map<string, string> attributes1;
  attributes1["id"] = "3";
  attributes1["name"] = "Device1";
  attributes1["uuid"] = "UniversalUniqueIdA";
  attributes1["sampleRate"] = "100.11";
  attributes1["iso841Class"] = "12";
  Device device1(attributes1);
  
  map<string, string> attributes2;
  attributes2["id"] = "5";
  attributes2["name"] = "Device2";
  attributes2["uuid"] = "UniversalUniqueIdA";
  attributes2["sampleRate"] = "100.11";
  attributes2["iso841Class"] = "12";
  Device device2(attributes2);
  
  map<string, string> attributes3;
  attributes3["id"] = "5";
  attributes3["name"] = "Device3";
  attributes3["uuid"] = "UniversalUniqueIdA";
  attributes3["sampleRate"] = "100.11";
  attributes3["iso841Class"] = "12";
  Device device3(attributes3);
  
  std::map<std::string, xmlpp::Element *> devices;
  XmlPrinter::getDeviceStream(root, &device1, devices);
  XmlPrinter::getDeviceStream(root, &device2, devices);
  XmlPrinter::getDeviceStream(root, &device3, devices);
  
  xmlpp::Node::NodeList list = root->get_children("DeviceStream");
  CPPUNIT_ASSERT_EQUAL((size_t) 3, list.size());
  
  xmlpp::Element *e = (xmlpp::Element*) list.front(); list.pop_front();
  CPPUNIT_ASSERT_EQUAL((string) e->get_attribute("name")->get_value(), (string) "Device1");
  e = (xmlpp::Element*) list.front(); list.pop_front();
  CPPUNIT_ASSERT_EQUAL((string) e->get_attribute("name")->get_value(), (string) "Device2");
  e = (xmlpp::Element*) list.front(); list.pop_front();
  CPPUNIT_ASSERT_EQUAL((string) e->get_attribute("name")->get_value(), (string) "Device3");
}

void XmlPrinterTest::testPrintError()
{
  PARSE_XML(XmlPrinter::printError(123, 9999, 1, "ERROR_CODE", "ERROR TEXT!"));
  
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Header@instanceId", "123");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Header@bufferSize", "9999");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Error@errorCode", "ERROR_CODE");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Error", "ERROR TEXT!");
}

void XmlPrinterTest::testPrintProbe()
{  
  PARSE_XML(XmlPrinter::printProbe(123, 9999, 1, devices));
    
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Header@instanceId", "123");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Header@bufferSize", "9999");
  
  // Check Axes
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Axes@name", "Axes");
  
  // Check Spindle
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Rotary@name", "C");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Rotary/m:DataItems/m:DataItem@type", "SPINDLE_SPEED");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Rotary/m:DataItems/m:DataItem[@type='ROTARY_MODE']@name",
                                    "Smode");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Rotary/m:DataItems/m:DataItem[@type='ROTARY_MODE']/m:Constraints/m:Value",
                                    "SPINDLE");
  
  // Check Linear Axis
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Linear[@name='X']/m:DataItems/m:DataItem@type", "POSITION");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Linear[@name='X']/m:DataItems/m:DataItem@name", "Xact");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Linear[@name='X']/m:DataItems/m:DataItem@significantDigits", "6");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Linear[@name='X']/m:DataItems/m:DataItem[@type='LOAD']//m:Maximum", "200");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Linear[@name='X']/m:DataItems/m:DataItem[@type='LOAD']/m:Constraints/m:Minimum", "0");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Linear[@name='X']/m:DataItems/m:DataItem[@type='LOAD']/m:Constraints/m:Maximum", "200");

  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Linear[@name='Z']/m:DataItems/m:DataItem@type", "POSITION");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Linear[@name='Z']/m:DataItems/m:DataItem@name", "Zact");
  
  // Check for Path component
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:Controller//m:Path/m:DataItems/m:DataItem[@type='PATH_POSITION']@name",
                                    "Ppos");

}

void XmlPrinterTest::testPrintCurrent()
{
  list<ComponentEvent *> events;
  
  events.push_back(addEventToDataItem("Xact", 10254804, "0"));
  events.push_back(addEventToDataItem("SspeedOvr", 15, "100"));
  events.push_back(addEventToDataItem("Xcom", 10254803, "0"));
  events.push_back(addEventToDataItem("spindle_speed", 16, "100"));
  events.push_back(addEventToDataItem("Yact", 10254797, "0.00199"));
  events.push_back(addEventToDataItem("Ycom", 10254800, "0.00189"));
  events.push_back(addEventToDataItem("Zact", 10254798, "0.0002"));
  events.push_back(addEventToDataItem("Zcom", 10254801, "0.0003"));
  events.push_back(addEventToDataItem("block", 10254789, "x-0.132010 y-0.158143"));
  events.push_back(addEventToDataItem("mode", 13, "AUTOMATIC"));
  events.push_back(addEventToDataItem("line", 10254796, "0"));
  events.push_back(addEventToDataItem("program", 12, "/home/mtconnect/simulator/spiral.ngc"));
  events.push_back(addEventToDataItem("execution", 10254795, "READY"));
  events.push_back(addEventToDataItem("power", 1, "ON"));
  
  list<DataItem *> dataItems;
  map<string, DataItem *> dataItemsMap = devices.front()->getDeviceDataItems();  
  map<string, DataItem*>::iterator data;
  for (data = dataItemsMap.begin(); data != dataItemsMap.end(); data++)
  {
    dataItems.push_back(data->second);
  }
  
  PARSE_XML(XmlPrinter::printCurrent(123, 131072, 10254805, 10123733, dataItems));
  
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='X']/m:Samples/m:Position[@name='Xact']", "0");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='C']/m:Samples/m:SpindleSpeed[@name='Sovr']", "100");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='X']/m:Samples/m:Position[@name='Xcom']", "0");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='C']/m:Samples/m:SpindleSpeed[@name='Sspeed']", "100");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='Y']/m:Samples/m:Position[@name='Yact']", "0.00199");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='Y']/m:Samples/m:Position[@name='Ycom']", "0.00189");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='Z']/m:Samples/m:Position[@name='Zact']", "0.0002");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='Z']/m:Samples/m:Position[@name='Zcom']", "0.0003");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='path']/m:Events/m:Block", 
                                    "x-0.132010 y-0.158143");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='path']/m:Events/m:Execution",
                                    "READY");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='path']/m:Events/m:ControllerMode",
                                    "AUTOMATIC");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='path']/m:Events/m:Line",
                                    "0");    
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='path']/m:Events/m:Program",
                                    "/home/mtconnect/simulator/spiral.ngc");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='power']/m:Events/m:PowerStatus",
                                    "ON");
  clearEvents(events);
}

void XmlPrinterTest::testPrintSample()
{
  list<ComponentEvent *> events;
  
  events.push_back(addEventToDataItem("Xact", 10843512, "0.553472"));
  events.push_back(addEventToDataItem("Xcom", 10843514, "0.551123"));
  events.push_back(addEventToDataItem("Xact", 10843516, "0.556826"));
  events.push_back(addEventToDataItem("Xcom", 10843518, "0.55582"));
  events.push_back(addEventToDataItem("Xact", 10843520, "0.560181"));
  events.push_back(addEventToDataItem("Yact", 10843513, "-0.900624"));
  events.push_back(addEventToDataItem("Ycom", 10843515, "-0.89692"));
  events.push_back(addEventToDataItem("Yact", 10843517, "-0.897574"));
  events.push_back(addEventToDataItem("Ycom", 10843519, "-0.894742"));
  events.push_back(addEventToDataItem("Xact", 10843521, "-0.895613"));
  events.push_back(addEventToDataItem("line", 11351720, "229"));
  events.push_back(addEventToDataItem("block", 11351726, "x-1.149250 y1.048981"));
    
  PARSE_XML(XmlPrinter::printSample(123, 131072, 10974584, 10843512, events));
  
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "/m:MTConnectStreams/m:Streams/m:DeviceStream/m:ComponentStream[@name='X']/m:Samples/m:Position[@name='Xact'][1]", 
                                    "0.553472");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='X']/m:Samples/m:Position[@name='Xact'][2]", 
                                    "0.556826");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='X']/m:Samples/m:Position[@name='Xcom'][1]", 
                                    "0.551123");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='X']/m:Samples/m:Position[@name='Xcom'][2]", 
                                    "0.55582");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='X']/m:Samples/m:Position[@name='Xact'][3]", 
                                    "0.560181");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='X']/m:Samples/m:Position[@name='Xact'][4]", 
                                    "-0.895613");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='Y']/m:Samples/m:Position[@name='Yact'][1]", 
                                    "-0.900624");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='Y']/m:Samples/m:Position[@name='Yact'][2]", 
                                    "-0.897574");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='Y']/m:Samples/m:Position[@name='Ycom'][1]", 
                                    "-0.89692");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='Y']/m:Samples/m:Position[@name='Ycom'][2]", 
                                    "-0.894742");
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='path']/m:Events/m:Line",
                                    "229");    
  CPPUNITTEST_ASSERT_XML_PATH_EQUAL(root, "//m:ComponentStream[@name='path']/m:Events/m:Block",
                                    "x-1.149250 y1.048981");    

  clearEvents(events);
}

DataItem * XmlPrinterTest::getDataItem(const char *name)
{
  Device *device = devices.front();
  CPPUNIT_ASSERT(device);
  
  return device->getDeviceDataItem(name);
}

ComponentEvent * XmlPrinterTest::addEventToDataItem(
    const char *name,
    unsigned int sequence,
    string value
  )
{
  string time("TIME");
  
  // Make sure the data item is there
  DataItem *d = getDataItem(name);
  CPPUNIT_ASSERT_MESSAGE((string) "Could not find data item " + name, d); 
  
  ComponentEvent *event = new ComponentEvent(*d, sequence, time, value);
  d->setLatestEvent(*event);
  return event;
}

void XmlPrinterTest::clearEvents(list<ComponentEvent *> events)
{
  list<ComponentEvent *>::iterator event;
  for (event = events.begin(); event != events.end(); event++)
  {
    delete (*event);
  }
}

