#include <eosiolib/eosio.hpp>

class proxyinfo_contract : public eosio::contract {
    public:
        proxyinfo_contract(account_name self)
        :eosio::contract(self),
        proxies(_self, _self)
        {}

        /**
         *  Set proxy info
         *
         *  @param proxy - the proxy account name
         *  @param name - human readable name
         *  @param slogan - a short description
         *  @param philosophy - voting philosophy
         *  @param background - optional. who is the proxy?
         *  @param website - optional. url to website
         *  @param logo_256 - optional. url to an image with the size of 256 x 256 px
         *  @param telegram - optional. telegram account name
         *  @param steemit - optional. steemit account name
         *  @param twitter - optional. twitter account name
         *  @param wechat - optional. wechat account name
         */

        void set(const account_name proxy, std::string name, std::string slogan, std::string philosophy, std::string background, std::string website, std::string logo_256, std::string telegram, std::string steemit, std::string twitter, std::string wechat) {
            // Validate input
            eosio_assert(!name.empty(), "name required");
            eosio_assert(name.length() <= 64, "name too long");

            eosio_assert(!slogan.empty(), "slogan required");
            eosio_assert(slogan.length() <= 64, "slogan too long");

            eosio_assert(!philosophy.empty(), "philosophy required");
            eosio_assert(philosophy.length() <= 1023, "philosophy too long");

            eosio_assert(background.length() <= 1023, "background too long");

            eosio_assert(website.length() <= 255, "website too long");
            if (!website.empty()) {
                eosio_assert(website.substr(0, 4) == "http", "website should begin with http");
            }

            eosio_assert(logo_256.length() <= 255, "logo_256 too long");
            if (!logo_256.empty()) {
                eosio_assert(logo_256.substr(0, 4) == "http", "logo_256 should begin with http");
            }

            eosio_assert(telegram.length() <= 64, "telegram too long");
            eosio_assert(steemit.length() <= 64, "steemit too long");
            eosio_assert(twitter.length() <= 64, "twitter too long");
            eosio_assert(wechat.length() <= 64, "wechat too long");

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
                    i.slogan = slogan;
                    i.philosophy = philosophy;
                    i.background = background;
                    i.logo_256 = logo_256;
                    i.telegram = telegram;
                    i.steemit = steemit;
                    i.twitter = twitter;
                    i.wechat = wechat;
                });

            // Insert
            } else {
                proxies.emplace(proxy, [&]( auto& i ) {
                    i.owner = proxy;
                    i.name = name;
                    i.website = website;
                    i.slogan = slogan;
                    i.philosophy = philosophy;
                    i.background = background;
                    i.logo_256 = logo_256;
                    i.telegram = telegram;
                    i.steemit = steemit;
                    i.twitter = twitter;
                    i.wechat = wechat;
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
            std::string slogan;
            std::string philosophy;
            std::string background;
            std::string logo_256;
            std::string telegram;
            std::string steemit;
            std::string twitter;
            std::string wechat;

            auto primary_key()const { return owner; }
            EOSLIB_SERIALIZE(proxy, (owner)(name)(website)(slogan)(philosophy)(background)(logo_256)(telegram)(steemit)(twitter)(wechat))
        };

        typedef eosio::multi_index<N(proxies), proxy> proxy_table;
        proxy_table proxies;
};

EOSIO_ABI(proxyinfo_contract, (set)(remove))