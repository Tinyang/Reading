Maven default lifecycle 包含如下 phase:
validate
initialize
generate-sources
process-sources
generate-resources
process-resources
compile
process-classes
generate-test-sources
process-test-sources
generate-test-resources
process-test-resources
test-compile
process-test-classes
test
prepare-package
package
pre-integration-test
integration-test
post-integration-test
verify
install
deploy

eg. 我们执行 mvn package会一直运行到package phase
eg. mvn compile会一直运行到compile phase

===============================
Maven clean lifecycle
pre-clean
clean （注意这个clean不是lifecycle而是phase）
post-clean

eg. mvn clean, Maven会自动执行clean生命周期,并执行到clean phase
===============================
所以,我们使用mvn这个命令时,后面的参数是phase,Maven自动根据生命周期运行到指定的phase。

eg. mvn clean install, Maven先执行clean生命周期到clean phase,再执行default生命周期到install phase
=============================== 
不常用的lifecycle site
Phase	         Description
pre-site	     execute processes needed prior to the actual project site generation
site	         generate the project's site documentation
post-site	     execute processes needed to finalize the site generation, and to prepare for site deployment
site-deploy	     deploy the generated site documentation to the specified web server


===============================
Goal
执行一个phase又会触发一个或多个goal
eg.
执行的Phase	       对应执行的Goal
compile	          compiler:compile
test	          compiler:testCompile
                  surefire:test
大多数情况,我们只要指定phase,就默认执行这些phase默认绑定的goal,只有少数情况,我们可以直接指定运行一个goal,例如,启动Tomcat服务器：
mvn tomcat:run

===============================
mvn compile
Maven 将会执行compile这个phase,这个phase会调用compiler插件执行关联的compiler:compiler这个goal
实际上,执行每个phase，都是通过某个plugin来执行的，Maven本身其实并不知道如何执行compile,他只是负责找到对应的compiler插件,来执行相应的goal

Maven内置的标准插件：
插件名称	  对应执行的phase
clean	      clean
compiler	  compile
surefire	  test
jar	          package

我们还可以使用自定义插件eg.maven-shade-plugin 

<build>
		<plugins>
			<plugin>
				<groupId>org.apache.maven.plugins</groupId>
				<artifactId>maven-shade-plugin</artifactId>
                <version>3.2.1</version>
				<executions>
					<execution>
						<phase>package</phase>
						<goals>
							<goal>shade</goal>
						</goals>
						<configuration>
                            ...
						</configuration>
					</execution>
				</executions>
			</plugin>
		</plugins>
</build>




