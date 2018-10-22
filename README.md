# EOS Proxy Info
This is an on-chain EOS contract (or dApp) that allows EOS proxy accounts to register additional information about themselves, such as name and website. This information is published on the EOS blockchain and freely available to be republished. An example website that uses this information is the [Aloha EOS Proxy Research Portal](https://www.alohaeos.com/vote/proxy).

The contract is published on the `regproxyinfo` account on the EOS mainnet.

## GUI Usage

For a GUI tool that interacts with this dApp try one of the following:

- [eostoolkit.io by GenerEOS](https://eostoolkit.io/vote/createproxy)
- [EOS Vote Tracker by EOS Mediterranean](https://votetracker.eosmedi.com/#/submit-proxy-info)
- [eos-voter by Greymass](https://github.com/greymass/eos-voter) (Tools -> Smart Contracts, then enter "regproxyinfo" and select "set")
- [MEET.ONE Wallet by MEET.ONE](https://meet.one/download/en?changelang=1)
- [MyEOSKit by EOS ASIA](https://www.myeoskit.com/#/tools/proxy)
- [TokenPocket](https://www.mytokenpocket.vip)

## Command Line Usage

First thing, you should already have an EOS proxy account that you have run `regproxy` on. If you haven't got that far, check out [EOS Proxy Voting: Everything You Need To Know](https://medium.com/coinmonks/eos-proxy-voting-everything-you-need-to-know-e4c9783249e3).

### Set

The set action inserts or updates information about your account. The paramaters are:
- **proxy** (required): Your EOS account name.
- **name** (required, 64 char max): The full name of your proxy.
- **slogan** (optional, 64 char max): A short description of your proxy intended to be shown in listings.
- **philosophy** (optional, 1024 char max): Description of proxy's voting philosophy.
- **background** (optional, 1024 char max): Background information / who is the proxy?
- **website** (optional, 256 char max): An http or https URL to a website, Reddit post, etc. with more information about your proxy.
- **logo_256** (optional, 256 char max): An http or https URL to an image with the size of 256 x 256 px.
- **telegram** (optional, 64 char max): Telegram account name.
- **steemit** (optional, 64 char max): Steemit account name.
- **twitter** (optional, 64 char max): Twitter account name.
- **wechat** (optional, 64 char max): WeChat account name.

Note: This action will consume a little bit of your RAM for the storage. How much depends on the length of your data, but probably around 1kb.

cleos example:
```
cleos -u https://api.main.alohaeos.com push action regproxyinfo set '["myproxyaccnt","My Proxy Name","For a better world","Voting philosophy","","https://my.proxy.website/","","","","",""]' -p myproxyaccnt
```

### Remove

The remove action will remove all information about your account. The parameters are:
- proxy: Your EOS account name.

cleos example:
```
cleos -u https://api.main.alohaeos.com push action regproxyinfo remove '["myproxyaccnt"]' -p myproxyaccnt

```

## Getting the Data

All data is stored in the `proxies` table on the `regproxyinfo` account.

cleos example:
```
cleos -u https://api.main.alohaeos.com get table regproxyinfo regproxyinfo proxies
{
  "rows": [{
      "owner": "myproxyaccnt",
      "name": "My Proxy Name",
      "website": "https://my.proxy.website/"
    }
  ],
  "more": false
}
```

curl example:
```
curl -d '{"json":true,"code":"regproxyinfo","scope":"regproxyinfo","table":"proxies","limit":100}' -s 'https://api.main.alohaeos.com/v1/chain/get_table_rows' | jq
{
  "rows": [{
      "owner": "myproxyaccnt",
      "name": "My Proxy Name",
      "website": "https://my.proxy.website/"
    }
  ],
  "more": false
}
```

## Feedback
Questions or comments? Swing by the [EOS VOTER PROXIES](https://t.me/eosproxies) channel on Telegram.

## Acknowledgements
These are the people or teams that helped contribute to this project (in alphabetical order):
- [Aloha EOS](https://www.alohaeos.com/) developed the initial version and maintains the regproxyinfo account.
- [DutchEOS](https://dutcheos.io/) helped test the initial version on mainnet.
- [EOS ASIA](https://www.eosasia.one/) for adding support to [MyEOSKit](https://www.myeoskit.com/#/tools/proxy).
- [EOS Mediterranean](https://eosmedi.com/) for adding support to [EOS Vote Tracker](https://votetracker.eosmedi.com/#/submit-proxy-info).
- [EOS Nation](https://eosnation.io) and their [Community Engagement Fund](https://www.youtube.com/watch?v=tUw8oWyFfeE) graciously funded the initial RAM purchase to publish on mainnet.
- [GenerEOS](https://www.genereos.io/) for adding support to [eostoolkit.io](https://eostoolkit.io/vote/createproxy).
