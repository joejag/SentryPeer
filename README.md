## SentryPeer<sup>&reg;</sup>

<img alt="SentryPeer Logo" src="https://raw.githubusercontent.com/SentryPeer/SentryPeer/main/web-gui-theme/src/assets/logo.svg" width="100" height="100"> 

A distributed list of bad actor IP addresses and phone numbers collected via a SIP Honeypot.

[![Stability: Experimental](https://masterminds.github.io/stability/experimental.svg)](https://masterminds.github.io/stability/experimental.html)
[![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/sentrypeer/sentrypeer?sort=semver)](https://github.com/SentryPeer/SentryPeer/releases)
[![Docker Hub](https://img.shields.io/badge/docker-hub-brightgreen.svg)](https://hub.docker.com/r/sentrypeer/sentrypeer)
[![Copr build status](https://copr.fedorainfracloud.org/coprs/ghenry/SentryPeer/package/sentrypeer/status_image/last_build.png)](https://copr.fedorainfracloud.org/coprs/ghenry/SentryPeer/package/sentrypeer/)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/23969/badge.svg)](https://scan.coverity.com/projects/sentrypeer-sentrypeer)
[![Build and Test](https://github.com/SentryPeer/SentryPeer/actions/workflows/main.yml/badge.svg)](https://github.com/SentryPeer/SentryPeer/actions/workflows/main.yml)
[![CodeQL](https://github.com/SentryPeer/SentryPeer/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/SentryPeer/SentryPeer/actions/workflows/codeql-analysis.yml)
[![Clang Static Analysis](https://github.com/SentryPeer/SentryPeer/actions/workflows/clang-analyzer.yml/badge.svg)](https://github.com/SentryPeer/SentryPeer/actions/workflows/clang-analyzer.yml)
[![Language grade: C](https://img.shields.io/lgtm/grade/cpp/g/SentryPeer/SentryPeer.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/SentryPeer/SentryPeer/context:cpp)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/SentryPeer/SentryPeer.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/SentryPeer/SentryPeer/alerts/)
[![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/5374/badge)](https://bestpractices.coreinfrastructure.org/projects/5374)

### Introduction

This is basically a fraud detection tool. It lets bad actors try to make phone calls and saves the IP address they came from and number they tried to call. Those details are then used to block them at the service providers network and the next time a user/customer tries to call a collected number, it's blocked.

Traditionally this data is shipped to a central place, so you don't own the data you've collected. This project is all about Peer to Peer sharing of that data. The user owning the data and various Service Provider / Network Provider related feeds of the data is the key bit for me. I'm sick of all the services out there that keep it and sell it. If you've collected it, you should have the choice to keep it and/or opt in to share it with other SentryPeer community members via p2p methods.

The sharing part...you only get other users' data if you [share yours](https://en.wikipedia.org/wiki/Tit_for_tat#Peer-to-peer_file_sharing). That's the key. It could be used (the sharing of data logic/feature) in many projects too if I get it right :-)

![Matrix](https://img.shields.io/matrix/sentrypeer:matrix.org?label=matrix&logo=matrix)
[![slack](https://img.shields.io/badge/join-us%20on%20slack-gray.svg?longCache=true&logo=slack&colorB=brightgreen)](https://join.slack.com/t/sentrypeer/shared_invite/zt-zxsmfdo7-iE0odNT2XyKLP9pt0lgbcw)
[![SentryPeer on Twitter](https://img.shields.io/badge/follow-twitter-blue)](https://twitter.com/SentryPeer)

### Screenshots

Here's a mockup of the web UI which is subject to change.

[![SentryPeer Web GUI mock up](./screenshots/SentryPeer-Web-GUI-screenshot.png)](./screenshots/SentryPeer-Web-GUI-screenshot.png)

### Goals

- [x] All code [Free/Libre and Open Source Software](https://www.gnu.org/philosophy/floss-and-foss.en.html)
- [x] FAST
- [x] User _owns their_ data
- [ ] User can submit their own data if they want to - _opt out_ (default is to submit data)
- [ ] User gets other users' data ([Tit for tat?](https://en.wikipedia.org/wiki/Tit_for_tat#Peer-to-peer_file_sharing)) **ONLY IF** they opt in to submit their data to the pool ([DHT](https://en.wikipedia.org/wiki/Distributed_hash_table)? - need to do a [PoC](https://en.wikipedia.org/wiki/Proof_of_concept))
- [ ] Peer to Peer sharing of data - [Zyre (Zeromq)](https://github.com/zeromq/zyre)
- [x] Multithreaded
- [x] UDP transport
- [ ] TCP transport
- [ ] TLS transport
- [ ] Data is max 7(?) days old as useless otherwise
- [x] SIP responsive mode can be enabled to collect data - cli / env flag   
- [x] **Local** data copy for **fast access** - cli / env db location flag
- [x] **Local** API for **fast access** - cli / env flag
- [x] **Local** Web GUI for **fast access** - cli / env flag
- [x] Query API for IP addresses of bad actors
- [ ] Query API for IPSET of bad actors
- [x] Query API for a particular IP address of a bad actor
- [x] Query API for attempted phone numbers called by bad actors
- [x] Query API for an attempted phone number called by a bad actor
- [x] [Fail2Ban](https://www.fail2ban.org/wiki/index.php/Main_Page) support via `syslog` as per [feature request](https://github.com/SentryPeer/SentryPeer/issues/6)
- [ ] Peer to Peer data replication - feature / cli flag
- [x] Local [sqlite](https://www.sqlite.org/index.html)/[lmdb](https://www.symas.com/symas-embedded-database-lmdb) database - feature / cli flag
- [ ] Analytics - opt in
- [ ] SDKs/libs for external access - [CGRateS](https://github.com/cgrates/cgrates) to start with or our own firewall with nftables
- [x] Small binary size for IoT usage
- [x] Cross-platform
- [ ] Firewall options to use distributed data in real time - [DHT](https://en.wikipedia.org/wiki/Distributed_hash_table)?
- [x] Container on [Docker Hub for latest build](https://hub.docker.com/r/sentrypeer/sentrypeer)
- [ ] BGP agent to peer with for blackholing collected IP addresses (similar to [Team Cymru Bogon Router Server Project](https://team-cymru.com/community-services/bogon-reference/bogon-reference-bgp/))
- [ ] SIP agent to return 404 or default destination for SIP redirects

### Design

TBD :-)

I started this because I wanted to do [C network programming](https://github.com/codeplea/Hands-On-Network-Programming-with-C) as all the projects I use daily are in C like [PostgreSQL](https://www.postgresql.org/), [OpenLDAP](https://www.openldap.org/), [FreeSWITCH](https://freeswitch.com/), [OpenSIPS](https://opensips.org/),
[Asterisk](https://www.asterisk.org/) etc. See
[Episode 414: Jens Gustedt on Modern C](https://www.se-radio.net/2020/06/episode-414-jens-gustedt-on-modern-c/) for why [C](https://en.wikipedia.org/wiki/C_(programming_language)) is a good choice.  For those interested, see my full podcast show list (https://www.se-radio.net/team/gavin-henry/) for [Software Engineering Radio](https://www.se-radio.net/)

### Talks

- TADSummit 2021 - https://blog.tadsummit.com/2021/11/17/sentrypeer/ 
- CommCon 2021 - https://2021.commcon.xyz/talks/sentrypeer-a-distributed-peer-to-peer-list-of-bad-ip-addresses-and-phone-numbers-collected-via-a-sip-honeypot

### Docker

You can run the latest version of SentryPeer with [Docker](https://www.docker.com/). The latest version is available from [Docker Hub](https://hub.docker.com/r/sentrypeer/sentrypeer/).
Or build yourself:

    sudo docker build -t sentrypeer .
    sudo docker run -d -p 5060:5060 -p 8082:8082 sentrypeer:latest

Then you can check at `http://localhost:8082/ip-addresses` and `http://localhost:5060/health-check` to see if it's running.

#### Environment Variables

    ENV SENTRYPEER_DB_FILE=/my/location/sentrypeer.db
    ENV SENTRYPEER_API=1
    ENV SENTRYPEER_WEB_GUI=1
    ENV SENTRYPEER_SIP_RESPONSIVE=1
    ENV SENTRYPEER_SYSLOG=1
    ENV SENTRYPEER_VERBOSE=1
    ENV SENTRYPEER_DEBUG=1

Either set these in the Dockerfile or in your `Dockerfile.env` file or docker run command.

### Installation
 
Debian or Fedora packages are always available from the release page for the current version of SentryPeer:

   https://github.com/SentryPeer/SentryPeer/releases

#### Building from source

You have two options for installation from source. CMake or autotools. Autotools is recommended at the moment. A release is an autotools build.

If you are a Fedora user, you can install this via [Fedora copr](https://copr.fedorainfracloud.org/coprs/):

[https://copr.fedorainfracloud.org/coprs/ghenry/SentryPeer/](https://copr.fedorainfracloud.org/coprs/ghenry/SentryPeer/)

If you are going to build from this repository, you will need to have the following installed:

  - `git`, `autoconf`, `automake` and `autoconf-archive` (Debian/Ubuntu) 
  - `libosip2-dev` (Debian/Ubuntu) or `libosip2-devel` (Fedora)
  - `libsqlite3-dev` (Debian/Ubuntu) or `sqlite-devel` (Fedora)
  - `uuid-dev` (Debian/Ubuntu) or `libuuid-devel` (Fedora)
  - `libmicrohttpd-dev` (Debian/Ubuntu) or `libmicrohttpd-devel` (Fedora)
  - `libjansson-dev` (Debian/Ubuntu) or `jansson-devel` (Fedora)
  - `libpcre2-dev` (Debian/Ubuntu) or `pcre2-devel` (Fedora)
  - `libcurl-dev` (Debian/Ubuntu) or `libcurl-devel` (Fedora)
  - `libcmocka-dev` (Debian/Ubuntu) or `libcmocka-devel` (Fedora) - for unit tests

Debian/Ubuntu:

    sudo apt-get install git build-essential autoconf-archive autoconf automake libosip2-dev libsqlite3-dev \
    libcmocka-dev uuid-dev libcurl-dev libpcre2-dev libjansson-dev libmicrohttpd-dev 

Fedora:

    sudo dnf install git autoconf automake autoconf-archive libosip2-devel libsqlite3-devel libcmocka-devel \
    libuuid-devel libmicrohttpd-devel jansson-devel libcurl-devel pcre2-devel

macOS:

    brew install git autoconf automake autoconf-archive libosip cmocka libmicrohttpd jansson curl pcre2

then (make check is highly recommended):

    ./bootstrap.sh
    ./configure
    make
    make check
    make install

Homebrew (macOS or Linux):

We have a [Homebrew Tap for this project](https://github.com/SentryPeer/homebrew-sentrypeer) (until we get more popular):

    brew tap sentrypeer/sentrypeer
    brew install sentrypeer

### Running SentryPeer

Once built, you can run like so to start in **debug mode**, **respond** to SIP probes, enable the **RESTful API**, enable
the Web GUI SPA and enable syslog logging ([use a package](https://github.com/SentryPeer/SentryPeer/releases) if you want [systemd](https://www.freedesktop.org/wiki/Software/systemd/)):

    ./sentrypeer -draws
    Starting sentrypeer...
    API mode enabled, starting http daemon...
    Web GUI mode enabled...
    Configuring local address...
    Creating socket...
    Binding socket to local address...
    Listening for incoming connections...
    SIP responsive mode enabled. Will reply to SIP probes...

when you get a probe request, you can see something like the following in the terminal:

```bash
Received (411 bytes): OPTIONS sip:100@XXX.XXX.XXX.XXX SIP/2.0
Via: SIP/2.0/UDP 91.223.3.152:5173;branch=z9hG4bK-515761064;rport
Content-Length: 0
From: "sipvicious"<sip:100@1.1.1.1>;tag=6434396633623535313363340131363131333837383137
Accept: application/sdp
User-Agent: friendly-scanner
To: "sipvicious"<sip:100@1.1.1.1>
Contact: sip:100@91.223.3.152:5173
CSeq: 1 OPTIONS
Call-ID: 679894155883566215079442
Max-Forwards: 70


read_packet_buf size is: 1024: 
read_packet_buf length is: 468: 
bytes_received size is: 411: 

Bad Actor is:
Event Timestamp: 2021-11-23 20:13:36.427515810
Event UUID: fac3fa20-8c2c-445b-8661-50a70fa9e873
SIP Message: OPTIONS sip:100@XXX.XXX.XXX.XXX SIP/2.0
Via: SIP/2.0/UDP 91.223.3.152:5173;branch=z9hG4bK-515761064;rport
From: "sipvicious" <sip:100@1.1.1.1>;tag=6434396633623535313363340131363131333837383137
To: "sipvicious" <sip:100@1.1.1.1>
Call-ID: 679894155883566215079442
CSeq: 1 OPTIONS
Contact: <sip:100@91.223.3.152:5173>
Accept: application/sdp
User-agent: friendly-scanner
Max-forwards: 70
Content-Length: 0


Source IP: 193.107.216.27
Called Number: 100
SIP Method: OPTIONS
Transport Type: UDP
User Agent: friendly-scanner
Collected Method: responsive
Created by Node Id: fac3fa20-8c2c-445b-8661-50a70fa9e873
SentryPeer db file location is: sentrypeer.db
Destination IP address of UDP packet is: xx.xx.xx.xx
```

You can see the data in the sqlite3 database called `sentrypeer.db` using [sqlitebrowser](https://sqlitebrowser.org/) or sqlite3 command line tool.

Here's a screenshot of the database opened using [sqlitebrowser](https://sqlitebrowser.org/) (it's big, so I'll just link to the image):

[sqlitebrowser exploring the sentrypeer.db](./screenshots/SentryPeer-sqlitebrowser.png)

### RESTful API 

The RESTful API is almost complete and the web UI is coming soon. Please click the Watch button to be notified when they are ready and hit Like to follow the development :-)

Right now you can call `/health-check`, like so:

```bash
curl -v -H "Content-Type: application/json" http://localhost:8082/health-check

* Connected to localhost (127.0.0.1) port 8082 (#0)
> GET /health-check HTTP/1.1
> Host: localhost:8082
> User-Agent: curl/7.79.1
> Accept: */*
> Content-Type: application/json
> 
* Mark bundle as not supporting multiuse
< HTTP/1.1 200 OK
< Date: Mon, 24 Jan 2022 11:16:25 GMT
< Content-Type: application/json
< Access-Control-Allow-Origin: *
< X-Powered-By: SentryPeer
< X-SentryPeer-Version: 1.0.0
< Content-Length: 81
< 
{
  "status": "OK",
  "message": "Hello from SentryPeer!",
  "version": "1.0.0"
}
```

and  `/ip-addresses`:

```bash
curl -v -H "Content-Type: application/json" http://localhost:8082/ip-addresses

* Connected to localhost (127.0.0.1) port 8082 (#0)
> GET /ip-addresses HTTP/1.1
> Host: localhost:8082
> User-Agent: curl/7.79.1
> Accept: */*
> Content-Type: application/json
> 
* Mark bundle as not supporting multiuse
< HTTP/1.1 200 OK
< Date: Mon, 24 Jan 2022 11:17:05 GMT
< Content-Type: application/json
< Access-Control-Allow-Origin: *
< X-Powered-By: SentryPeer
< X-SentryPeer-Version: 1.0.0
< Content-Length: 50175
< 
{
  "ip_addresses_total": 396,
  "ip_addresses": [
    {
      "ip_address": "193.107.216.27",
      "seen_last": "2022-01-11 13:30:48.703603359",
      "seen_count":	"1263"
    },
    {
      "ip_address": "193.46.255.152"
      "seen_last": "2022-01-11 13:28:27.348926406",
      "seen_count": "3220"      
    }
    ...
  ]
}
```

and a single IP address query `/ip-address/{ip-address}`:

```bash
curl -v -H "Content-Type: application/json" http://localhost:8082/ip-address/8.8.8.8

* Connected to localhost (127.0.0.1) port 8082 (#0)
> GET /ip-addresses/8.8.8.8 HTTP/1.1
> Host: localhost:8082
> User-Agent: curl/7.79.1
> Accept: */*
> Content-Type: application/json
> 
* Mark bundle as not supporting multiuse
< HTTP/1.1 404 Not Found
< Date: Mon, 24 Jan 2022 11:17:57 GMT
< Content-Type: application/json
< Access-Control-Allow-Origin: *
< X-Powered-By: SentryPeer
< X-SentryPeer-Version: 1.0.0
< Content-Length: 33
< 
* Connection #0 to host localhost left intact
{
  "message": "No bad actor found"
}
```

and lastly a phone number query for a number a bad actor tried to call:

```bash
curl -v -H "Content-Type: application/json" http://localhost:8082/numbers/8784946812410967

* Connected to localhost (127.0.0.1) port 8082 (#0)
> GET /numbers/8784946812410967 HTTP/1.1
> Host: localhost:8082
> User-Agent: curl/7.79.1
> Accept: */*
> Content-Type: application/json
> 
* Mark bundle as not supporting multiuse
< HTTP/1.1 200 OK
< Date: Mon, 24 Jan 2022 11:19:53 GMT
< Content-Type: application/json
< Access-Control-Allow-Origin: *
< X-Powered-By: SentryPeer
< X-SentryPeer-Version: 1.0.0
< Content-Length: 46
< 
{
  "phone_number_found": "8784946812410967"
}
```

### Syslog and Fail2ban

With `sentrypeer -s`, you parse syslog and use Fail2Ban to block the IP address of the bad actor.

```syslog
Nov 30 21:32:16 localhost.localdomain sentrypeer[303741]: Source IP: 144.21.55.36, Method: OPTIONS, Agent: sipsak 0.9.7
```

### IPv6 Multicast Address

The project has an IANA IPv6 multicast address for the purpose of sending messages between SentryPeer peers.

    Addresses: FF0X:0:0:0:0:0:0:172
    Description: SentryPeer
    Contact: Gavin Henry <ghenry at sentrypeer.org>
    Registration Date: 2022-01-26

Please see http://www.iana.org/assignments/ipv6-multicast-addresses

The assigned variable-scope address -- which can also be listed as "FF0X::172" for short -- the "X" denotes any possible scope.

### License
 
Great reading - [How to choose a license for your own work](https://www.gnu.org/licenses/license-recommendations.en.html)

This work is dual-licensed under GPL 2.0 and GPL 3.0.

`SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only`

### Contributing

See [CONTRIBUTING](./CONTRIBUTING.md)

### Project Website

https://sentrypeer.org

### Trademark

[**SENTRYPEER** is a registered trademark](https://trademarks.ipo.gov.uk/ipo-tmcase/page/Results/1/UK00003700947) of Gavin Henry

### Questions, Bug reports, Feature Requests

New issues can be raised at:

https://github.com/ghenry/SentryPeer/issues

It's okay to raise an issue to ask a question.

### Special Thanks

Special thanks to:

  - [David Miller](http://davidmiller.io/) for the design of the SentryPeer [Web GUI theme](./web-gui-theme) and [logo](./web-gui-theme/src/assets/logo.svg). Very kind of you!
  - [@garymiller](https://github.com/garyemiller) for the feature request of syslog and Fail2ban as per [ Fail2ban Integration via syslog #6](https://github.com/SentryPeer/SentryPeer/issues/6) 

