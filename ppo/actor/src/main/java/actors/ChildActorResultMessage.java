package actors;

import searchers.SearchSiteInfo;

public class ChildActorResultMessage {
    public String response;
    public SearchSiteInfo info;

    public ChildActorResultMessage(String response, SearchSiteInfo info) {
        this.response = response;
        this.info = info;
    }
}
