#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int main (int argc, char *argv[])
{
  
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  NodeContainer nodes;
  nodes.Create (2);
  
  NodeContainer nodes2;
  nodes2.Add(nodes.Get(1));  
  nodes2.Create(2);
  
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("8Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("3ms"));

  PointToPointHelper pointToPoint2;
  pointToPoint2.SetDeviceAttribute ("DataRate", StringValue ("7Mbps"));
  pointToPoint2.SetChannelAttribute ("Delay", StringValue ("1ms"));

  PointToPointHelper pointToPoint1;
  pointToPoint1.SetDeviceAttribute ("DataRate", StringValue ("7Mbps"));
  pointToPoint1.SetChannelAttribute ("Delay", StringValue ("1ms"));

  NetDeviceContainer devices;
  devices = pointToPoint.Install (nodes);

  NetDeviceContainer devices2;
  devices2 = pointToPoint2.Install (nodes2.Get(1),nodes2.Get(2));
  
  NetDeviceContainer devices1;
  devices1 = pointToPoint1.Install (nodes2.Get(0),nodes2.Get(1));

  InternetStackHelper stack;
  stack.Install (nodes.Get(0));
  stack.Install (nodes2);
  
 

  Ipv4AddressHelper address,address2,address1;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  address2.SetBase ("10.1.3.0", "255.255.255.0");
  address1.SetBase ("10.1.2.0", "255.255.255.0");
 

  Ipv4InterfaceContainer interfaces = address.Assign (devices);
  Ipv4InterfaceContainer interfaces2 = address2.Assign (devices2);
  Ipv4InterfaceContainer interfaces1 = address1.Assign (devices1);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  UdpEchoServerHelper echoServer1 (10);

  ApplicationContainer serverApps1 = echoServer1.Install (nodes2.Get (0));
  serverApps1.Start (Seconds (1.0));
  serverApps1.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient1 (interfaces1.GetAddress (0), 10);
  echoClient1.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient1.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient1.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps1= echoClient1.Install (nodes2.Get (1));
  clientApps1.Start (Seconds (3.0));
  clientApps1.Stop (Seconds (10.0));

  UdpEchoServerHelper echoServer2 (11);

  ApplicationContainer serverApps2 = echoServer2.Install (nodes2.Get (0));
  serverApps2.Start (Seconds (1.0));
  serverApps2.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient2 (interfaces1.GetAddress (0), 11);
  echoClient2.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient2.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient2.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps2= echoClient2.Install (nodes2.Get (2));
  clientApps2.Start (Seconds (4.0));
  clientApps2.Stop (Seconds (10.0));

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
