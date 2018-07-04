#include <eosiolib/eosio.hpp>

class proxyinfo_contract : public eosio::contract {
    public:
        proxyinfo_contract(account_name self)
        :eosio::contract(self),
        proxies(_self, _self)
        {}

        void set(const account_name proxy, std::string name, std::string website) {
            // Validate input
            eosio_assert(!name.empty(), "name required");
            eosio_assert(name.length() <= 64, "name too long");
            eosio_assert(!website.empty(), "website required");
            eosio_assert(website.length() <= 255, "website too long");
            eosio_assert(website.substr(0, 4) == "http", "website should begin with http");

            // Require auth from the proxy account
            require_auth(proxy);

            // Check if exists
            auto current = proxies.find(proxy);

            // Update
            if (current != proxies.end()) {
                proxies.modify(current, proxy, [&]( auto& i ) {
                    i.owner = proxy;
                    i.name = name;
                    i.website = website;
                });

            // Insert
            } else {
                proxies.emplace(proxy, [&]( auto& i ) {
                    i.owner = proxy;
                    i.name = name;
                    i.website = website;
                });
            }
        }

        void remove(const account_name proxy) {
            // Require auth from the proxy account
            require_auth(proxy);

            // Delete record
            auto lookup = proxies.find(proxy);
            proxies.erase(lookup);
        }

    private:
        // @abi table proxies i64
        struct proxy {
            account_name owner;
            std::string name;
            std::string website;

            auto primary_key()const { return owner; }
            EOSLIB_SERIALIZE(proxy, (owner)(name)(website))
        };

        typedef eosio::multi_index<N(proxies), proxy> proxy_table;
        proxy_table proxies;
};

EOSIO_ABI(proxyinfo_contract, (set)(remove))