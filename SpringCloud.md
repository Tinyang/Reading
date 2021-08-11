Spring Cloud	https://docs.spring.io/spring-cloud-config/docs/3.0.4/reference/html/

Spring Cloud provides tools for develops to quickly build some of the common patterns in distributed systems (e.g. configuration management, service discovery, circuit breakers, intelligent routing, micro-proxy, control bus). Coordination of distributed systems leads to boiler plate patterns, and using Spring Cloud developers can quickly stand up services and applications that implement those patterns. They will work well in any distributed environment, including the developer’s own laptop, bare metal data centers, and managed platforms such as Cloud Foundry.

1.	Features
Spring Cloud focuses on providing good out of box experience for typical use cases and extensibility mechanism to cover others.
	Distributed/versioned configuration
	Service registration and discovery
	Routing
	Service-to-service calls
	Load balancing
	Circuit Breakers
	Distributed messaging
2.	Spring Cloud Bus
Spring Cloud Bus links the nodes of a distributed system with a lightweight message broker. This broker can then be used to broadcast changes (such as configuration changes) or other management instructions. A key idea is that the bus is like a distributed actuator for a Spring Boot application that is scaled out. However, it can also be used as a communication channel between apps. This project provides starters for either an AMQP broker or Kafka as the transport.
3.	Spring Cloud Config
Spring Cloud Config provides server-side and client-side support for externalized configuration in a distributed system. With the Config server, you have a central place to manage external properties for applications across all environments. The concepts on both client and server map identically to the Spring Environment and PropertySource abstraction running in any language. As an application moves through the deployment pipeline from dev to test and into production, you can manage the configuration between those environments and be certain that applications have everything they need to run when they migrate. The default implementation of the server storage backend uses git, so it easily supports labelled versions of configuration environments as well as being accessible to a wide range of tooling for managing the content. It is easy to add alternative implementations and plug them in with Spring Configuration.
4.	Spring Cloud Zookeeper
This project provides Zookeeper integrations for Spring Boot applications through autoconfiguration and binding to the Spring Environment and other Spring programming model idioms. With a few annotations, you can quickly enable and configure the common patterns inside your application and build large distributed systems with Zookeeper based components. The provided patterns include Service Discovery and Configuration. The project also provides client-side load-balancing via integration with Spring Cloud LoadBalancer.
