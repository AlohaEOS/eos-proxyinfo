# EOS Proxy Info
This is an on-chain EOS contract (or dApp) that allows EOS proxy accounts to register additional information about themselves, such as name and website. This information is public, on the blockchain and freely available to be republished. An example website that uses this information is the [Aloha EOS Proxy Research Portal](https://www.alohaeos.com/vote/proxy).

The contract is published on the `regproxyinfo` account on the EOS Mainnet.

## Usage

First thing, you should already have an EOS proxy account that you have run `regproxy` on. If you haven't got that far, check out [EOS Proxy Voting: Everything You Need To Know](https://medium.com/coinmonks/eos-proxy-voting-everything-you-need-to-know-e4c9783249e3).

### Set

The set action inserts or updates information about your account. The paramaters are:
- proxy: Your EOS account name.
- name: The full name of your proxy.
- website: An http or https URL to a website, Reddit post, etc. with more information about your proxy.

Note: This action will consume a little bit of your RAM for the storage. How much depends on the length of your data, but probably 200-500 bytes.

cleos example:
```
cleos -u https://api.main.alohaeos.com push action regproxyinfo set '["myproxyaccnt","My Proxy Name","https://my.proxy.website/"]' -p myproxyaccnt
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
